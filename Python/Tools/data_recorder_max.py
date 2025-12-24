import rhinoscriptsyntax as rs
import scriptcontext as sc
import Grasshopper as gh

# Initialize recorded data storage
if 'recorded_data' not in globals() or reset:
    recorded_data = []  # Reset the recorded data when reset button is pressed

# Set maximum number of records (connect this to Grasshopper input)
if 'max_records' not in globals():
    max_records = 100  # Default fallback

# Append new data if recording is enabled
if record:
    recorded_data.append(data)  # 'data' is the input value to record

    # Remove oldest items if we exceed max_records
    while len(recorded_data) > max_records:
        recorded_data.pop(0)  # Remove first (oldest) item

# Output recorded data
recorded_output = recorded_data
