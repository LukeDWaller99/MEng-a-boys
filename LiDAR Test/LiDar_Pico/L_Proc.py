#VL53 data processing functions - J Pendlebury 2023
# Use these functions to do stuff to the arrays passed by the ToF sensors.

#this function takes the distance list and finds the dimensions - 4x4 or 8x8
# RET: 4 if 4x4, 8 if 8x8 mode

def average(lst):
    return sum(lst)/len(lst)

def diag_print(data,sensor_mode):
    """
    Prints default diagnostic infomation, including basic outputs.
    
    Args:
    - data: A tuple of distance readings from a square sensor grid.
    - mode: An integer representing sensor mode

    Returns:
    NULL
    """
    data_length = len(data.distance)
    print("{}mm {}% (avg: {}mm {}%)".format(
        data.distance[0],
        data.reflectance[0],
        data.distance_avg,
        data.reflectance_avg))
    print("TL={} TR={} BL={} BR={}".format(
        data.distance[55],
        data.distance[63],
        data.distance[0],
        data.distance[7]))
    lst_low= data.distance[0:8]
    lst_top= data.distance[-8:64]
    print("TOP={} LOW={} LEFT={} RIGHT={}".format(
        average(lst_top),
        average(lst_low),
        average(grab_left(data.distance,sensor_mode)),
        average(grab_right(data.distance,sensor_mode))))
    print("Number of distance samples:",data_length)

def calc_mode(distances):
    """
    Uses powers to find the sensor mode. By taking the square root of the length of the data list,
    the size of the sensor grid can be found, and thus the mode calculated.
    
    Args:
    - distances: A list of distance readings from a square sensor grid.

    Returns:
    - An integer representing the sensor mode
    """
    return int(len(distances)**(1/2))

def grab_left(distances,mode):
    """
    Grabs values along the left edge of the sensor grid. Works in both modes.
    
    Assumes row-major order.
    
    Args:
    - distances: A list of distance readings from a square sensor grid.
    - mode: An integer representing sensor mode

    Returns:
    - A list of the left edge readings of the sensor grid.
    """
    left_edge_data = []
    for i in range(mode):
    # Calculate the index of the sensor on the left edge of the current row
        left_edge_index = i * mode
    # Append the sensor data at the calculated index to the left_edge_data list
        left_edge_data.append(distances[left_edge_index])
    return left_edge_data

def grab_right(distances,mode):
    """
    Grabs values along the right edge of the sensor grid. Works in both modes.
    
    Assumes row-major order.
    
    Args:
    - distances: A list of distance readings from a square sensor grid.
    - mode: An integer representing sensor mode

    Returns:
    - A list of the right edge readings of the sensor grid.
    """
    right_edge_data = []
    for i in range(mode):
    # Calculate the index of the sensor on the right edge of the current row
        right_edge_index = i * mode + (mode - 1)
    # Append the sensor data at the calculated index to the right_edge_data list
        right_edge_data.append(distances[right_edge_index])
    return right_edge_data

#this function grabs the centre half of the distances tuple.
#Prioritises readings from straight ahead.
def centre_grid(distances,mode):
    """
    Extracts the middle 4 readings from a square sensor grid.

    Assumes that the readings are arranged in row-major order.

    Args:
    - distances: A list of distance readings from a square sensor grid.
    - mode: An integer representing sensor mode

    Returns:
    - A list of the middle 4 readings in the sensor grid.
    """
    # Extract the middle 2x2 grid of readings from the center of the sensor grid
    if grid_size == 4:
        middle_readings = [
            distances[5], distances[6],
            distances[9], distances[10]
        ]
    # Extract the middle 4x4 grid of readings from the center of the sensor grid
    elif grid_size == 8:
        middle_readings = [
            distances[19], distances[20], distances[21], distances[22],
            distances[27], distances[28], distances[29], distances[30],
            distances[35], distances[36], distances[37], distances[38],
            distances[43], distances[44], distances[45], distances[46]
        ]
    else:
        raise ValueError("Unsupported grid size")

    return middle_readings#

def centre_grid_avg(centre_grid):
    """
    Returns the average of the centre values of the sensor grid.

    Args:
    - centre_grid: a list of the centre values extracted by centre_grid function

    Returns:
    - A float value of the average distance reading of the centre of the grid.
    """
    return average(centre_grid)