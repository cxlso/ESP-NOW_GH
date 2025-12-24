"""
Threshold-Based State Hold Filter

Description:
A stateful filter that stabilizes noisy inputs by only updating output
when the change exceeds a specified threshold. Small fluctuations are
ignored, and the previous value is held. Supports single values and lists.

Inputs:
    x        : float or list of floats
               Incoming value(s) to be filtered.
    threshold: float
               Minimum change required to update the output.
    reset    : bool
               If True, reinitializes the filter with current input.

Output:
    a        : float or list of floats
               Filtered output; updates only on meaningful changes.
"""

# Initialize previous values
if 'prev_x' not in globals() or reset:
    prev_x = x

# Check if inputs are lists or single values
if isinstance(x, list):
    # Make sure prev_x is a list of same length
    if not isinstance(prev_x, list) or len(prev_x) != len(x):
        prev_x = x

    result = []
    for xi, pxi in zip(x, prev_x):
        if abs(xi - pxi) >= threshold:
            result.append(xi)
        else:
            result.append(pxi)
    prev_x = result  # update previous values to the current filtered result
else:
    if abs(x - prev_x) >= threshold:
        result = x
        prev_x = x
    else:
        result = prev_x

# Output
a = result
