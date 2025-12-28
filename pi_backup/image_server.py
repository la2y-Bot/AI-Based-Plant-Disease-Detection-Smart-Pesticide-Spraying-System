from flask import Flask, send_file
from flask_cors import CORS
import os

SAVE_DIR = "/home/pi/captures"
app = Flask(__name__)
CORS(app)  # ✅ allows access from your website

@app.route("/latest.jpg")
def latest_image():
    path = os.path.join(SAVE_DIR, "latest.jpg")
    if not os.path.exists(path):
        return "No image yet", 404
    return send_file(path, mimetype="image/jpeg")

@app.route("/")
def home():
    return """
    <html><body style='text-align:center;font-family:sans-serif'>
      <h3>Latest Image from Pi</h3>
      <img id='pic' src='/latest.jpg?ts=0' width='480'>
      <script>
        setInterval(()=>{document.getElementById('pic').src='/latest.jpg?ts='+Date.now();},2000);
      </script>
    </body></html>
    """

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
