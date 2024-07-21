import matplotlib.pyplot as plt
import numpy as np
import serial

# Establish a serial connection
serial_connection = serial.Serial('COM12', 115200)  # Full path to COM port

# Create the phasor diagram plot
fig, ax = plt.subplots()

# Initialize quiver objects for each phase
phasor_A = ax.quiver(0, 0, 0, 0, angles='xy', scale_units='xy', scale=1, color='r', label="Phase A")
phasor_B = ax.quiver(0, 0, 0, 0, angles='xy', scale_units='xy', scale=1, color='g', label="Phase B")
phasor_C = ax.quiver(0, 0, 0, 0, angles='xy', scale_units='xy', scale=1, color='b', label="Phase C")

# Set plot labels and title
ax.set_xlabel("Real Axis")
ax.set_ylabel("Imaginary Axis")
ax.set_title("Phasor Diagram")
ax.grid(True)
ax.axhline(0, color='black', linewidth=0.5)
ax.axvline(0, color='black', linewidth=0.5)
ax.set_aspect('equal', 'box')
ax.legend()

# Initialize lists to store data for each phase
phase_A_data = []
phase_B_data = []
phase_C_data = []

# Function to update the plot with new data
def update_plot(phasor, data, angle_rad):
    if data:
        x, y = data[-1]
        phasor.set_UVC(x, y)
        # Annotate with the angle value
        ax.legend([f"Angle: {(angle_rad):.2f}°"], loc='upper left')
        plt.draw()
        plt.pause(0.01)

# Read and process the incoming data
while True:
    line = serial_connection.readline().decode('utf-8').strip()
    print(line)
    parts = line.split(",")
    if len(parts) == 3:
        angle_rad_A = float(parts[0])
        angle_rad_B = float(parts[1])
        angle_rad_C = float(parts[2])
        
        # Calculate the x and y components for each phase
        x_component_A = np.cos(angle_rad_A)
        y_component_A = np.sin(angle_rad_A)
        
        x_component_B = np.cos(angle_rad_B)
        y_component_B = np.sin(angle_rad_B)
        
        x_component_C = np.cos(angle_rad_C)
        y_component_C = np.sin(angle_rad_C)
        
        # Update the data for each phase
        phase_A_data.append((x_component_A, y_component_A))
        phase_B_data.append((x_component_B, y_component_B))
        phase_C_data.append((x_component_C, y_component_C))
        
        # Update the plot
        update_plot(phasor_A, phase_A_data, angle_rad_A)
        update_plot(phasor_B, phase_B_data, angle_rad_B)
        update_plot(phasor_C, phase_C_data, angle_rad_C)
