# Обновление Palisade на sunnypilot dev 2026-10-10

## База и объединение

- Предыдущий порт: `7b4b192a2d`, база `0b2c431d3a`.
- Новый upstream: `6c7564969016b91e28aafa3a167300f8731e875a`,
  `sunnypilot v2026.10.06-4920`, опубликован 2026-10-07.
- Upstream dev заменён новым снимком без общей истории. Трёхстороннее
  объединение выполнено через `git merge-tree --write-tree` с явно заданной
  базой `0b2c431d3a`. Итоговый merge-коммит сохраняет родителей порта и upstream.
- Резервная локальная ветка: `codex/pal23sp-before-dev-20261010`.
- Сохранены адаптация Palisade, DBC, fingerprints, safety, параметры управления,
  список автомобилей и локальная настройка FFmpeg в `launch_env.sh`.

## Разрешение конфликта safety

Upstream добавляет блокировку AEB_StopReq в бите 55 обычного SCC12.
Для blended Palisade ускорение передаётся в SCC11, где биты 52-57 —
ComfortBandUpper. Новая AEB-проверка применяется только без blended-флага,
сохраняя обновлённую защиту обычных Hyundai и раскладку Palisade.
Добавлен тест всех 64 значений поля comfort band.

## Прошивка

Версия: `DEV-6c756496-pal23-DEBUG`. Номер в версии обозначает upstream-базу
с адаптацией Palisade, а не SHA итогового merge-коммита.

SHA-256 `panda/board/obj/panda_h7.bin.signed`:
`797b326be63ecfbe655963be19713a6cfb655ab14dfd558d8d7f2652fc6f1189`.

Сборка выполнена из объединённых исходников в отдельном каталоге устройства:
`/data/tmp/panda-dev-pal23sp-20261010`.
Использованы команды startup/main из нового `compile_commands.json`, штатный
linker script, адрес вектора `0x08020000`, objcopy и штатная подпись через
`panda/board/crypto/sign.py` с репозиторным debug-сертификатом. Хеши протоколов
в флагах компиляции сверены с актуальными заголовками.

Обновлены локальные main.elf, main.bin, signed binary, gitversion.h и version.
Прочие готовые артефакты обновлены из upstream. Проверены наличие обеих blended
RX-таблиц в ELF, длина signed image, VERS-маркер и RSA-подпись.

## Проверки и границы

- Hyundai safety и car interface: 1441 passed, 171 skipped,
  1806 subtests passed.
- Новый `TestHyundaiBlendedAebLayout`: 1 passed, 64 subtests passed.
- Дополнительная проверка blended TX для разных comfort band — PASS.
- Воспроизведение маршрута `00000001--2d89e67a1e--0` через новую libsafety:
  149536 CAN-кадров без RX-отказов; после начального заполнения проверки валидны.
- Изменения относительно upstream проходят `git diff --check`.
  Пробельные замечания в неизменённых файлах upstream не исправлялись.

Полный sunnypilot на устройстве не обновлялся, новая Panda не прошивалась.
Работа modeld, UI и управление на автомобиле на этой базе не проверены.
Для установки следует обновлять sunnypilot и его Panda как согласованный комплект.
Локальные диагностические `tmp_can_*.py` в коммит не включаются.
