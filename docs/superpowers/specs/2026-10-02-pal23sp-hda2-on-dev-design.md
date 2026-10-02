# Перенос pal23sp-hda2 на sunnypilot dev

## Цель

Hyundai Palisade 2023–24 и Kia Telluride 2023–24 с HDA II должны определяться и управляться на текущем `sunnypilot` `dev` так же, как на кончике ветки `bryangerlach/openpilot` `pal23sp-hda2`. Переносится итоговое поведение этой ветки: платформа, DBC, продольный контроль, руление, ESCC, ICBM, damp и safety.

Успех: на локальной ветке от `dev` платформа `HYUNDAI_PALISADE_2023` собирается вместе с существующими тестами Hyundai, а машины без флага `CAN_CANFD_BLENDED` сохраняют поведение `dev`.

## База

- Приёмник: `sunnypilot/sunnypilot` ветка `dev`, коммит `0b2c431d3abab630df0a32f53236944855a91aa3`. Каталог `C:\Users\Jack\sunnypilot-pal23sp`, локальная ветка `pal23sp-hda2-dev`. Пуша нет.
- Источник поведения: дерево opendbc `d458b4419f1da35136f78f0c6aaef4a9b7368f60`, на которое указывает кончик `pal23sp-hda2`.
- Патч ложится на уже встроенный в `dev` каталог `opendbc_repo`. Подмодули не возвращаются.
- Берётся кумулятивное дерево кончика, а не повтор промежуточных мержей.

## Платформа

В `opendbc/car/hyundai/values.py` добавляется `HYUNDAI_PALISADE_2023`:

- документы: Hyundai Palisade (with HDA II) 2023–24, колодка `hyundai_r`; Kia Telluride (with HDA II) 2023–24, колодка `hyundai_p`;
- `specs` копируются с `HYUNDAI_PALISADE` (2020–22);
- флаги: `CHECKSUM_CRC8 | CAN_CANFD_BLENDED | CANFD_RADAR_SCC`.

`HyundaiPlatformConfig.init` при `CAN_CANFD_BLENDED` ставит DBC `{Bus.pt: "hyundai_palisade_2023_generated"}`.

Имя автомобиля берётся из platform config. Отдельный enum `CAR` добавляется только если `dev` больше не выводит его из конфигов платформ.

Биты флагов на кончике pal23: `HyundaiFlags.CAN_CANFD_BLENDED = 2**27`, `HyundaiSafetyFlags.CAN_CANFD_BLENDED = 2**10`. Перед записью проверить, что эти биты на `dev` свободны. Если бит занят, берётся следующий свободный бит того же enum, и одно и то же значение используется в car-коде и в safety.

Лимиты руля в `CarControllerParams` для этого флага: `STEER_MAX 384`, `STEER_DRIVER_ALLOWANCE 50`, `STEER_THRESHOLD 150`, `STEER_DELTA_UP 2`, `STEER_DELTA_DOWN 3`.

В `opendbc/car/torque_data/override.toml` добавляется `"HYUNDAI_PALISADE_2023" = [2.32, 2.32, 0.1]`.

В `fingerprints.py` добавляется блок `CAR.HYUNDAI_PALISADE_2023`: камера `0x7c4` (семь FW) и радар `0x7d0` (пять FW) с кончика pal23.

## DBC

Источник `opendbc/dbc/generator/hyundai/hyundai_palisade_2023.dbc` заменяется версией с кончика pal23 (937 строк против 865 на `dev`). Имя, которое читает рантайм, — `hyundai_palisade_2023_generated`. Если на `dev` лежит сгенерированная копия, она пересобирается штатным генератором репозитория. Вручную сгенерированный файл не правится.

## Продольное управление и состояние

Для `CAN_CANFD_BLENDED`:

- круиз читается с `SCC12`, а не с `SCC11`;
- BSM ищется на шине ECAN (`0x58b`);
- LDA включается флагом `HAS_LDA_BUTTON` вместе с наличием `0x391` на шине 0;
- лимит скорости и `HAS_LKAS12` выставляются по флагу, даже если `0x544` / `0x53E` в отпечатке нет;
- при открытом продольном контроле и выключенных camera SCC и ESCC радар глушится по `0x7d0` на ECAN;
- `stoppingDecelRate = 0.4` остаётся закомментированным, как на кончике ветки;
- в `CarState` для blended пишется `dawStatus` из `ALERTS_364.DAW_Status`. Для остальных машин поле остаётся значением по умолчанию capnp (`0`). Запасное `6` с кончика pal23 для не-blended машин не переносится;
- парсеры `Bus.pt` и `Bus.cam` для blended сидят на ECAN и CAM соответственно;
- скорость с камеры `LKAS12` для blended читается с шины pt, а не с `cp_cam`;
- валидность цели радара для blended считается так же, как для `CANFD_CAMERA_SCC`: `ACC_ObjDist < 204.6`.

Продольные команды идут через `create_acc_commands_can_canfd_blended` (SCC11/12/14). Отмена и resume идут через `create_clu11` с `Buttons.CANCEL` и `Buttons.RES_ACCEL`, а не через CAN-FD кнопки. `create_clu11` получает `CAN` и прокидывает его в ICBM: сигнатура `create_can_mock_button_messages` и оба вызова.

## Руление

`create_steering_messages` для этой платформы получает `frame`, `torque_fault`, линии полос, предупреждения схода и `vEgo`. `torque_fault` — это `latActive and not apply_steer_req`.

Damp: `Damping_Gain` 50 при `vEgo < 29.0576`, иначе 85. `NEW_SIGNAL_5` 100 при `vEgo < 65`, иначе 133. HUD полос и `CF_Lkas_ToiFlt` заполняются в `create_lkas11_can_canfd_blended`.

`create_lfahda_cluster` и `create_adrv_messages` получают флаг blended. Если blended и ESCC выключен, дополнительно уходят `create_radar_aux_messages`.

Сигнатуры меняются вместе со всеми вызовами в файлах Hyundai. Путь без флага сохраняет аргументы и сообщения `dev`.

`escc.py` на `dev` и на кончике pal23 совпадает побайтно и не меняется.

## Safety

Правки только в `opendbc_repo/opendbc/safety/modes/hyundai.h`. В `panda/` своей копии `hyundai.h` нет.

Для HDA2 blended:

- отдельные RX/TX: `hyundai_can_canfd_blended_hda2_rx_checks`, `hyundai_can_canfd_blended_hda2_long_rx_checks`, `HYUNDAI_CAN_CANFD_BLENDED_HDA2_TX_MSGS`, `HYUNDAI_CAN_CANFD_BLENDED_HDA2_LONG_TX_MSGS`;
- счётчик и чексумма `0x421` берутся из байтов blended-раскладки (`data[1] >> 4` и `data[0]`), а не из обычного SCC;
- `pt_bus = 1`, `scc_bus = 1`;
- круиз и ускорение читаются из blended-раскладки `0x421`;
- лимит момента `HYUNDAI_STEERING_LIMITS_CAN_CANFD_BLENDED = HYUNDAI_LIMITS(384, 2, 3, 250)` — допуск водителя в safety равен 250. Это другое число, чем `STEER_DRIVER_ALLOWANCE = 50` в car-параметрах, и оба значения сохраняются как на кончике;
- рулевой TX для blended проверяется по `0x50`.

Макросы `HYUNDAI_COMMON_TX_MSGS`, `HYUNDAI_LONG_COMMON_TX_MSGS`, `HYUNDAI_COMMON_RX_CHECKS` и `HYUNDAI_SCC12_ADDR_CHECK` получают аргумент blended и на пути без флага дают прежние размеры, периоды и проверки.

## Схема

В `opendbc/car/car.capnp`, внутри `CarState`, добавляется `dawStatus @62 :UInt8`. На `dev` `@61` занят `carNotReady`, `@62` свободен. `carstate.py` пишет это поле только для blended.

Сдвиги номеров `dawLevel1` / `dawLevel2` в `cereal/log.capnp` и любые другие поля capnp в перенос не входят.

## Файлы

Меняются только пути под `opendbc_repo/`:

- `opendbc/car/hyundai/values.py`
- `opendbc/car/hyundai/interface.py`
- `opendbc/car/hyundai/carstate.py`
- `opendbc/car/hyundai/carcontroller.py`
- `opendbc/car/hyundai/hyundaican.py`
- `opendbc/car/hyundai/hyundaicanfd.py`
- `opendbc/car/hyundai/fingerprints.py`
- `opendbc/car/car.capnp`
- `opendbc/car/torque_data/override.toml`
- `opendbc/dbc/generator/hyundai/hyundai_palisade_2023.dbc`
- `opendbc/safety/modes/hyundai.h`
- `opendbc/sunnypilot/car/hyundai/icbm.py`
- `opendbc/sunnypilot/car/hyundai/carstate_ext.py`
- `opendbc/sunnypilot/car/hyundai/radar_interface_ext.py`

`opendbc/car/hyundai/radar_interface.py` и `opendbc/sunnypilot/car/hyundai/escc.py` совпадают с `dev` и не трогаются.

Если `dev` с момента `0b2c431` разъехался с pal23 внутри этих файлов, конфликт решается по смыслу патча blended. Окружающий код `dev` остаётся.

## Проверка

Уже существующие `opendbc/safety/tests/test_hyundai.py` и `opendbc/safety/tests/hyundai_common.py` на кончике pal23 и на `dev` совпадают побайтно. Их не менять. После переноса они должны проходить: путь без флага blended обязан остаться прежним.

`opendbc/car/hyundai/tests/test_hyundai.py` тоже прогоняется, если файл есть на `dev`. Отдельных тестов blended на кончике нет, новые тесты не добавляются.

Прогон на автомобиле в эту работу не входит.

## Вне переноса

- повтор истории мержей pal23;
- возврат git-подмодулей;
- правки `cereal/log.capnp`;
- пуш и pull request.
