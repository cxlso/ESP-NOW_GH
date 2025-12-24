"""
Running Total Accumulator

Description:
Keeps a cumulative sum of incoming numbers. The total persists across
component updates and can be reset when needed.

Inputs:
    x     : float
            New number to add to the running total.
    reset : bool
            If True, resets the total to zero.

Output:
    a     : float
            Current running total.
"""

# Initialize total if not already set or if reset is True
if 'total' not in globals() or reset:
    total = 0

# Add new incoming value
total += x  # where 'x' is your input number

# Output the running total
a = total