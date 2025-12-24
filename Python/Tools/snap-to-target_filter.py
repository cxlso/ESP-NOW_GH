"""
Snap-to-Target Filter

Description:
Updates values to match a target only when the difference is within a
specified threshold. Values outside the threshold remain unchanged.
Supports both single numbers and lists.

Inputs:
    a_list   : float or list of floats
               Original value(s) to be filtered.
    b_list   : float or list of floats
               Target value(s) to snap to if within threshold.
    threshold: float
               Maximum difference allowed for snapping.

Output:
    a        : float or list of floats
               Snapped or original value(s) after threshold filtering.
"""


# Check if both inputs are lists
if isinstance(a_list, list) and isinstance(b_list, list):
    result = []
    for ai, bi in zip(a_list, b_list):
        if abs(ai - bi) <= threshold:
            result.append(bi)  # snap to target
        else:
            result.append(ai)  # keep original
else:
    # Single numbers case
    if abs(a_list - b_list) <= threshold:
        result = b_list
    else:
        result = a_list

# Output
a = result
