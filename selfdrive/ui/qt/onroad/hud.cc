#include "selfdrive/ui/qt/onroad/hud.h"

#include <cmath>

#include "selfdrive/ui/qt/util.h"

#include "common/params_keys.h"

static bool enable_attention_visual = false;
static bool enable_attention_alert = false;
static uint64_t last_param_check = 0;

constexpr int SET_SPEED_NA = 255;

HudRenderer::HudRenderer() {}

void HudRenderer::updateState(const UIState &s) {
  is_metric = s.scene.is_metric;
  status = s.status;

  const SubMaster &sm = *(s.sm);
  if (sm.rcv_frame("carState") < s.scene.started_frame) {
    is_cruise_set = false;
    set_speed = SET_SPEED_NA;
    speed = 0.0;
    daw = 5;
    return;
  }

  const auto &controls_state = sm["controlsState"].getControlsState();
  const auto &car_state = sm["carState"].getCarState();

  // Handle older routes where vCruiseCluster is not set
  set_speed = car_state.getVCruiseCluster() == 0.0 ? controls_state.getVCruiseDEPRECATED() : car_state.getVCruiseCluster();
  is_cruise_set = set_speed > 0 && set_speed != SET_SPEED_NA;
  is_cruise_available = set_speed != -1;

  if (is_cruise_set && !is_metric) {
    set_speed *= KM_TO_MILE;
  }

  daw = car_state.getDawStatus();

  // Handle older routes where vEgoCluster is not set
  v_ego_cluster_seen = v_ego_cluster_seen || car_state.getVEgoCluster() != 0.0;
  float v_ego = v_ego_cluster_seen ? car_state.getVEgoCluster() : car_state.getVEgo();
  speed = std::max<float>(0.0f, v_ego * (is_metric ? MS_TO_KPH : MS_TO_MPH));

  uint64_t now = millis_since_boot();
  if (now - last_param_check > 1000) {
    Params params;
    enable_attention_visual = params.getBool("EnableAttentionVisual");
    enable_attention_alert = params.getBool("EnableAttentionAlert");
    last_param_check = now;
  }
}

void HudRenderer::draw(QPainter &p, const QRect &surface_rect) {
  p.save();

  // Draw header gradient
  QLinearGradient bg(0, UI_HEADER_HEIGHT - (UI_HEADER_HEIGHT / 2.5), 0, UI_HEADER_HEIGHT);
  bg.setColorAt(0, QColor::fromRgbF(0, 0, 0, 0.45));
  bg.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
  p.fillRect(0, 0, surface_rect.width(), UI_HEADER_HEIGHT, bg);

#ifndef SUNNYPILOT
  if (is_cruise_available) {
    drawSetSpeed(p, surface_rect);
  }
  drawCurrentSpeed(p, surface_rect);
#endif
  if (enable_attention_visual) {
    drawDAWStatus(p, surface_rect);
  }

  p.restore();
}

void HudRenderer::drawDAWStatus(QPainter &p, const QRect &surface_rect) {
  // Determine box color
  QColor box_color;
  if (daw == 5) {
    box_color = QColor(0x80, 0xd8, 0xa6, 204);  // green
  } else if (daw >= 2 && daw <= 4) {
    box_color = QColor(255, 204, 0, 204);       // yellow
  } else if (daw == 1) {
    box_color = QColor(255, 0, 0, 204);         // red
  } else {
    return;  // Invalid or unsupported level
  }

  // Match the size of the set speed box
  const QSize default_size = {172, 204};
  QSize daw_box_size = is_metric ? QSize(200, 204) : default_size;

  // Position below the set speed box
  int x = 60 + (default_size.width() - daw_box_size.width()) / 2;
  int y = 45 + daw_box_size.height() + 20;  // 20 px below set speed

  QRect daw_rect(QPoint(x, y), daw_box_size);

  // Border color (translucent white)
  QColor border_color = QColor(255, 255, 255, 75);

  // Draw rounded background box
  p.setPen(QPen(border_color, 6));
  p.setBrush(box_color);
  p.drawRoundedRect(daw_rect, 32, 32);

  // Label text: "DAW"
  QRect label_rect = daw_rect.adjusted(0, 15, 0, -140);
  p.setFont(InterFont(35, QFont::DemiBold));
  p.setPen(Qt::white);
  p.drawText(label_rect, Qt::AlignHCenter | Qt::AlignTop, "DAW");

  // Draw DAW level number
  QString daw_str = QString::number(daw);
  p.setFont(InterFont(90, QFont::Bold));
  p.setPen(Qt::white);
  p.drawText(daw_rect.adjusted(0, 77, 0, 0), Qt::AlignTop | Qt::AlignHCenter, daw_str);
}

void HudRenderer::drawSetSpeed(QPainter &p, const QRect &surface_rect) {
  // Draw outer box + border to contain set speed
  const QSize default_size = {172, 204};
  QSize set_speed_size = is_metric ? QSize(200, 204) : default_size;
  QRect set_speed_rect(QPoint(60 + (default_size.width() - set_speed_size.width()) / 2, 45), set_speed_size);

  // Draw set speed box
  p.setPen(QPen(QColor(255, 255, 255, 75), 6));
  p.setBrush(QColor(0, 0, 0, 166));
  p.drawRoundedRect(set_speed_rect, 32, 32);

  // Colors based on status
  QColor max_color = QColor(0xa6, 0xa6, 0xa6, 0xff);
  QColor set_speed_color = QColor(0x72, 0x72, 0x72, 0xff);
  if (is_cruise_set) {
    set_speed_color = QColor(255, 255, 255);
    if (status == STATUS_DISENGAGED) {
      max_color = QColor(255, 255, 255);
    } else if (status == STATUS_OVERRIDE) {
      max_color = QColor(0x91, 0x9b, 0x95, 0xff);
    } else {
      max_color = QColor(0x80, 0xd8, 0xa6, 0xff);
    }
  }

  // Draw "MAX" text
  p.setFont(InterFont(40, QFont::DemiBold));
  p.setPen(max_color);
  p.drawText(set_speed_rect.adjusted(0, 27, 0, 0), Qt::AlignTop | Qt::AlignHCenter, tr("MAX"));

  // Draw set speed
  QString setSpeedStr = is_cruise_set ? QString::number(std::nearbyint(set_speed)) : "–";
  p.setFont(InterFont(90, QFont::Bold));
  p.setPen(set_speed_color);
  p.drawText(set_speed_rect.adjusted(0, 77, 0, 0), Qt::AlignTop | Qt::AlignHCenter, setSpeedStr);
}

void HudRenderer::drawCurrentSpeed(QPainter &p, const QRect &surface_rect) {
  QString speedStr = QString::number(std::nearbyint(speed));

  p.setFont(InterFont(176, QFont::Bold));
  drawText(p, surface_rect.center().x(), 210, speedStr);

  p.setFont(InterFont(66));
  drawText(p, surface_rect.center().x(), 290, is_metric ? tr("km/h") : tr("mph"), 200);
}

void HudRenderer::drawText(QPainter &p, int x, int y, const QString &text, int alpha) {
  QRect real_rect = p.fontMetrics().boundingRect(text);
  real_rect.moveCenter({x, y - real_rect.height() / 2});

  p.setPen(QColor(0xff, 0xff, 0xff, alpha));
  p.drawText(real_rect.x(), real_rect.bottom(), text);
}
