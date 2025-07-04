# 🛒 Smart Check Out

**Smart Check Out** is an IoT + Web-based billing solution designed to eliminate long queues in supermarkets. It streamlines the checkout process by allowing customers to scan items directly from smart trolleys and pay without traditional billing counters.

---

## 🚀 Features

* 📱 **Smart Trolley System**: Each trolley has an ESP8266 module that scans product barcodes and sends data to the cloud.
* 🔐 **QR-based Access**: Customers scan a QR code on the trolley to view their current cart in real time.
* 💻 **Customer Dashboard**: View scanned items, update quantities, or remove items from the cart.
* 🧾 **Employee Dashboard**: Cashiers can manage trolleys, review scanned items, and process payments.
* ☁️ **Cloud Integration**: Product data is stored and managed on MongoDB Atlas.
* 📡 **Flask Backend**: Acts as the central API hub for managing product scans, billing, and dashboards.

---

## 🧱 Architecture Overview

1. **ESP8266 Web Server**:

   * Hosts a local page to scan barcodes via mobile.
   * Automatically sends scanned product ID + trolley ID to Flask API (`/api/add_product`) over HTTP POST.

2. **Flask Backend**:

   * Routes:

     * `/api/add_product`: Adds scanned products to the DB.
     * `/trolley/<trolley_id>`: Customer dashboard.
     * `/employee/login`: Employee login.
     * `/employee/dashboard`: Dashboard to manage trolleys and billing.
   * Connects to **MongoDB Atlas** for storing products, trolley info, and billing data.

3. **MongoDB Collections**:

   * `mainproducts`: All product data with fields: `productid`, `name`, `mrp`, `discount`, `price`.
   * `productentries`: Scanned product entries with `trolley_id`, `timestamp`, and `billed`.
   * `trolleyids`: Registered trolleys with `trolleyid` and `lastbilledstamp`.
   * `employee_credentials`: Login credentials and roles (e.g., cashier).

---

## 📁 Project Structure

```
smart-check-out/
│
├── esp8266_code/            # ESP8266 firmware
│   └── smart_trolley.ino
│
├── static/                  # CSS/JS/Assets
│
├── templates/               # HTML Pages
│   ├── trolley.html
│   ├── employee_dashboard.html
│   └── login.html
│
├── app.py                   # Flask backend
├── requirements.txt         # Python dependencies
└── README.md                # You're here!
```

---

## 🧑‍💻 Technologies Used

* **ESP8266** – For wireless communication and barcode scanning
* **Flask** – Python backend framework
* **MongoDB Atlas** – Cloud NoSQL database
* **HTML/CSS + Tailwind CSS** – Frontend design
* **JavaScript** – Client-side logic
* **QR Code Integration** – Customer access via trolley QR codes

---

## ✅ How It Works (Flow)

1. ESP8266 connects to Wi-Fi and hosts a scanner interface.
2. Customer scans a barcode, which is sent to the Flask server.
3. Flask stores the entry in `productentries` with timestamp and trolley ID.
4. Customer scans the trolley's QR code → redirected to `/trolley/<trolley_id>`.
5. Dashboard displays only unbilled items (based on `lastbilledstamp`).
6. After shopping, cashier logs in and searches for the trolley.
7. Cashier processes the bill → system marks items as billed and updates the `lastbilledstamp`.

---

## 🔒 Authentication

* Employee login system via `/employee/login`.
* Credentials are verified from `employee_credentials` collection.

---

## 💡 Future Improvements

* ✅ Real-time updates via WebSocket
* ⏳ Mobile payment gateway integration
* 📷 Camera-based auto-barcode recognition
* 📊 Admin analytics dashboard

---

## 🛠️ Setup Instructions

1. **Clone the repository**

   ```bash
   git clone https://github.com/yourusername/smart-check-out.git
   cd smart-check-out
   ```

2. **Install Python dependencies**

   ```bash
   pip install -r requirements.txt
   ```

3. **Configure MongoDB**

   * Replace MongoDB URI in `app.py`:

     ```python
     client = MongoClient("YOUR_MONGODB_ATLAS_URI")
     ```

4. **Run the Flask App**

   ```bash
   python app.py
   ```

5. **Flash ESP8266**

   * Upload `esp8266_code/smart_trolley.ino` to the board using Arduino IDE.

---

## 📸 Screenshots

Coming soon...

---

## 🤝 Contributions

Pull requests, suggestions, and improvements are welcome!

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
