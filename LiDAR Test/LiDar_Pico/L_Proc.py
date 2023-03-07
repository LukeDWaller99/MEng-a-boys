#VL53 data processing functions - J Pendlebury 2023
# Use these functions to do stuff to the arrays passed by the ToF sensors.

def grab_left(distances,mode):
    left_edge_data = []
    for i in range(mode):
    # Calculate the index of the sensor on the left edge of the current row
        left_edge_index = i * mode
    # Append the sensor data at the calculated index to the left_edge_data list
        left_edge_data.append(distances[left_edge_index])
    return left_edge_data

def grab_right(distances,mode):
    right_edge_data = []
    for i in range(mode):
    # Calculate the index of the sensor on the right edge of the current row
        right_edge_index = i * mode + (mode - 1)
    # Append the sensor data at the calculated index to the right_edge_data list
        right_edge_data.append(distances[right_edge_index])
    return right_edge_data