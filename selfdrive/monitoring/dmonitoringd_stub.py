#!/usr/bin/env python3
"""
Заглушка для driverMonitoringState когда камера водителя отключена
"""
import time
import cereal.messaging as messaging
from openpilot.common.realtime import config_realtime_process

def main():
    config_realtime_process([0, 1, 2, 3], 5)

    pm = messaging.PubMaster(['driverStateV2','driverMonitoringState'])

    # Создаем заглушку driverMonitoringState на основе примера из simulated_sensors.py
    while True:
        dat = messaging.new_message('driverStateV2')
        dat.driverStateV2.leftDriverData.faceOrientation = [0., 0., 0.]
        dat.driverStateV2.leftDriverData.faceProb = 1.0
        dat.driverStateV2.rightDriverData.faceOrientation = [0., 0., 0.]
        dat.driverStateV2.rightDriverData.faceProb = 1.0
        pm.send('driverStateV2', dat)
        msg = messaging.new_message('driverMonitoringState', valid=True)
        msg.driverMonitoringState = {
            "faceDetected": True,
            "isDistracted": False,
            "awarenessStatus": 1.0,
        }
        pm.send('driverMonitoringState', msg)
        time.sleep(0.05)  # 20Hz

if __name__ == "__main__":
    main()
