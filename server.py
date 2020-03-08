from flask import Flask, render_template, request
import os
import serial
import time
# from flask_cors import CORS

app = Flask(__name__)
# CORS(app)
ser = serial.Serial("/dev/cu.usbmodem14101", 9600)

@app.route('/')
def index():
    console.log("top")


@app.route('/arduino/<num>')
def write_serial(num):
    number = int(num)
    if(number >= 0 and number < 5):
        ser.write(bytes(num, 'utf-8'))
        print("送信")
        print(bytes(num, 'utf-8'))
        time.sleep(5)


@app.route('/arduino/close')
def close_setrial():
    ser.close()


if __name__ == '__main__':
    app.debug = True
    app.run(host="localhost", port="33565")