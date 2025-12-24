# Inputs:
#   data: string or number to store
# Outputs:
#   status: feedback message for panel

import os

if data is not None:
    buffer_path = os.path.join(os.getenv('TEMP'), "gh_buffer.txt")
    try:
        with open(buffer_path, "w") as f:
            f.write(str(data))
        status = "Data written to: {}".format(buffer_path)
    except Exception as e:
        status = "Write error: {}".format(e)
else:
    status = "No input data received"
