import os, time, shutil
from datetime import datetime
from picamera2 import Picamera2
import firebase_admin
from firebase_admin import credentials, db
from gradio_client import Client, handle_file

# ---------------- CONFIG -------------------
SERVICE_ACCOUNT = "/home/pi/serviceAccountKey.json"
DATABASE_URL = "https://picamcontrol-default-rtdb.firebaseio.com/"
MODEL_NAME = "sanchit-jakhetia/BioTech"
SAVE_DIR = "/home/pi/captures"
# -------------------------------------------

os.makedirs(SAVE_DIR, exist_ok=True)

cred = credentials.Certificate(SERVICE_ACCOUNT)
firebase_admin.initialize_app(cred, {"databaseURL": DATABASE_URL})

ref = db.reference("/cameraCommand/value")
results_ref = db.reference("/results")

cam = Picamera2()
cam.configure(cam.create_still_configuration())
cam.start()

client = Client(MODEL_NAME)

print("✅ Pi Firebase + HuggingFace Listener Started...")

while True:
    try:
        val = ref.get()
        if val == "click":
            ref.set("inprocess")

            ts = int(time.time())
            filename = f"image_{ts}.jpg"
            filepath = os.path.join(SAVE_DIR, filename)
            latest_path = os.path.join(SAVE_DIR, "latest.jpg")

            cam.capture_file(filepath)
            print(f"📸 Captured: {filename}")

            # copy this capture as latest.jpg
            try:
                shutil.copy(filepath, latest_path)
                print("📁 Copied to latest.jpg for website display")
            except Exception as e:
                print("⚠ Copy failed:", e)

            # Send to Hugging Face
            try:
                result = client.predict(img=handle_file(filepath), api_name="/predict")
                label = result.get("label", str(result))
            except Exception as e:
                label = f"error: {e}"

            results_ref.set({
                "label": label,
                "time": datetime.now().isoformat(),
                "image": "latest.jpg"
            })
            print(f"🧠 Prediction: {label}")

            # delete old timestamped image
            try:
                os.remove(filepath)
                print("🗑 Deleted timestamped image")
            except:
                pass

            ref.set("done")

        time.sleep(0.3)

    except KeyboardInterrupt:
        print("\nExiting...")
        break
    except Exception as e:
        print("⚠ Error:", e)
        time.sleep(1)
