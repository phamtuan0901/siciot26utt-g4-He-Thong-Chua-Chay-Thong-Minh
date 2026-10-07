import paho.mqtt.client as mqtt
import json

from config import MQTT_BROKER, MQTT_PORT, MQTT_TOPIC


class MQTTHandler:

    def __init__(self):

        self.client = mqtt.Client()

        try:

            self.client.connect(
                MQTT_BROKER,
                MQTT_PORT,
                60
            )

            print("[MQTT] Da ket noi toi Broker")

        except Exception as e:

            print(f"[MQTT] Khong ket noi duoc: {e}")

            self.client = None

    def publish(self, data):

        if self.client is None:
            return

        payload = json.dumps(data)

        self.client.publish(
            MQTT_TOPIC,
            payload,
            qos=0,
            retain=False
        )

        print(f"[MQTT] {payload}")