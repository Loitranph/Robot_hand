# Robot Hand Project

## 📌 Overview
This project is a **robotic hand** controlled via Python, designed for educational and research purposes in mechatronics and robotics.  
It demonstrates integration between **mechanical design, electronics, and programming** to perform grasping and gesture-based tasks.

## 🎯 Features
- **Finger control** using servo motors.
- **Customizable gestures** through software.
- **Serial communication** between the computer and microcontroller.
- **Python-based control interface** for flexibility and expandability.
- **Easy hardware assembly** with modular design.

## 🛠️ Hardware Requirements
- Robotic hand frame (3D printed or pre-built)
- Servo motors (SG90 / MG996R or similar)
- Arduino board (Uno/Nano/MEGA)
- Jumper wires
- Power supply (5V)

## 💻 Software Requirements
- Python 3.x
- Arduino IDE
- Required Python libraries:
  ```bash
  pip install pyserial
  ```
- Servo control library for Arduino

## ⚙️ Setup Instructions
1. **Assemble the robotic hand** and mount servo motors.
2. **Upload the Arduino control code** from the `arduino_code` folder to your Arduino board.
3. **Connect the Arduino** to your computer via USB.
4. **Run the Python control script** to send commands to the robotic hand.
   ```bash
   python robot_hand_control.py
   ```

## 🚀 Future Improvements
- Implement **computer vision** for gesture recognition.
- Add **wireless control** using Bluetooth or Wi-Fi.
- Improve **grip precision** with feedback sensors.
