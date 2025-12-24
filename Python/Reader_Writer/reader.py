# Outputs:
#   data
#   status

import os

buffer_path = os.path.join(os.getenv('TEMP'), "gh_buffer.txt")

if os.path.exists(buffer_path):
    try:
        with open(buffer_path, "r") as f:
            data = f.read()
        status = "Data read successfully"
    except Exception as e:
        data = None
        status = "Read error: {}".format(e)
else:
    data = None
    status = "Buffer file not found"