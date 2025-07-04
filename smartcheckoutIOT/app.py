from flask import Flask, request, jsonify
from flask_cors import CORS
from pymongo import MongoClient
from datetime import datetime, timezone
import os

app = Flask(__name__)
CORS(app)

# MongoDB Atlas connection
MONGO_URI = "mongodb+srv://smartcheckout:smartcheckout@smartcheckout.z6jaqh9.mongodb.net/?retryWrites=true&w=majority&appName=Smartcheckout"
client = MongoClient(MONGO_URI)
db = client["smartcheckout"]
product_collection = db["products"]

@app.route('/api/add_product', methods=['POST'])
def add_product():
    data = request.get_json()

    product_id = data.get("product_id")
    trolley_id = data.get("trolley_id")
    quantity = data.get("quantity")

    if not product_id or not trolley_id:
        return jsonify({"error": "Missing product_id or trolley_id"}), 400

    document = {
        "product_id": product_id,
        "trolley_id": trolley_id,
        "quantity": int(quantity),
        "timestamp": datetime.now(timezone.utc),
        "billed": False
    }

    result = product_collection.insert_one(document)

    return jsonify({
        "message": "Product added successfully",
        "id": str(result.inserted_id)
    }), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
