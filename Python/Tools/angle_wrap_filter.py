"""
Angle Wrap Filter

Description:
Normalizes an input angle into the range [-300, 300] degrees. 
Angles beyond this range are wrapped by adding or subtracting 360 degrees.

Inputs:
    x : float
        Input angle in degrees.

Output:
    a : float
        Wrapped angle within [-300, 300].
"""

# Assume 'x' comes in as an input
if x >= 300:
    result = x - 360
elif x <= -300:
    result = x + 360
else:
    result = x

# Output
a = result  # Connect 'a' to the Grasshopper output
