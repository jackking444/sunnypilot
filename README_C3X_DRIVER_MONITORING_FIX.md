# Исправление ошибки "Communication Issue between Processes driverMonitoringState" в C3X

## Проблема
После отключения камеры водителя система падает с ошибкой "Communication Issue between Processes driverMonitoringState". Это происходит потому, что процессы мониторинга водителя (`dmonitoringd` и `dmonitoringmodeld`) не могут получить данные от камеры водителя.

## Причина
1. **dmonitoringmodeld** - модель мониторинга водителя, которая обрабатывает видео с камеры водителя
2. **dmonitoringd** - процесс мониторинга водителя, который зависит от `dmonitoringmodeld`
3. Когда камера водителя отключена, эти процессы не могут работать и система выдает ошибку связи

## Решение
Нужно отключить процессы мониторинга водителя и создать заглушку для `driverMonitoringState`.

## Способы исправления

### Способ 1: Полное исправление (рекомендуется)
```bash
# Сделать скрипт исполняемым
chmod +x fix_driver_monitoring_communication.sh

# Запустить полное исправление
./fix_driver_monitoring_communication.sh

# Перезагрузить устройство
sudo reboot
```

### Способ 2: Быстрое исправление
```bash
# Сделать скрипт исполняемым
chmod +x quick_fix_driver_monitoring.sh

# Запустить быстрое исправление
./quick_fix_driver_monitoring.sh

# Перезагрузить устройство
sudo reboot
```

### Способ 3: Ручное исправление
```bash
# Установить переменную окружения
export DISABLE_DRIVER=1

# Добавить в /etc/environment для постоянного отключения
echo "DISABLE_DRIVER=1" | sudo tee -a /etc/environment

# Остановить процессы мониторинга водителя
pkill -f "dmonitoringd" || true
pkill -f "dmonitoringmodeld" || true

# Перезагрузить устройство
sudo reboot
```

## Как это работает

### 1. Отключение процессов
В `system/manager/process_config.py` процессы `dmonitoringd` и `dmonitoringmodeld` отключаются или заменяются заглушками.

### 2. Заглушка для driverMonitoringState
Создается заглушка, которая отправляет пустые данные `driverMonitoringState`, чтобы система не падала с ошибкой связи.

### 3. Переменная окружения DISABLE_DRIVER
Устанавливается `DISABLE_DRIVER=1` для отключения камеры водителя на уровне `camerad`.

## Проверка статуса

### Автоматическая проверка
```bash
# Проверить процессы мониторинга водителя
pgrep -f "dmonitoringd"
pgrep -f "dmonitoringmodeld"

# Проверить переменную окружения
echo $DISABLE_DRIVER

# Проверить в /etc/environment
grep DISABLE_DRIVER /etc/environment
```

### Проверка логов
```bash
# Проверить логи на ошибки связи
tail -f /data/openpilot/log.txt | grep -i "communication\|driverMonitoringState"
```

## Восстановление мониторинга водителя

Если камера водителя будет исправлена, выполните:

```bash
# Удалить переменную из /etc/environment
sudo sed -i '/DISABLE_DRIVER=1/d' /etc/environment

# Удалить системный сервис
sudo systemctl disable disable-driver-camera.service
sudo rm /etc/systemd/system/disable-driver-camera.service

# Восстановить оригинальные файлы из .backup
cp /data/openpilot/system/manager/process_config.py.backup /data/openpilot/system/manager/process_config.py

# Перезагрузить устройство
sudo reboot
```

## Примечания

- Отключение мониторинга водителя не влияет на основную функциональность openpilot
- Система будет работать без предупреждений о невнимательности водителя
- Это временное решение до ремонта или замены камеры водителя
- Функции мониторинга водителя будут недоступны

## Связанные файлы

- `system/manager/process_config.py` - конфигурация процессов
- `selfdrive/monitoring/dmonitoringd.py` - процесс мониторинга водителя
- `selfdrive/modeld/dmonitoringmodeld.py` - модель мониторинга водителя
- `system/camerad/cameras/hw.h` - конфигурация камер
