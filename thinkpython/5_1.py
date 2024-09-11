import time

# get the current timestamp
current_time = time.time()

# calculate total seconds since the epoch
total_seconds = int(current_time)

# calculate days, hours, minutes, and seconds
days = total_seconds // 86400  # 86400 seconds = 1 day
hours = (total_seconds % 86400) // 3600  # 3600 seconds = 1 hour
minutes = (total_seconds % 3600) // 60  # 60 seconds = 1 minute
seconds = total_seconds % 60

# output the result
print(f"time since epoch: {days} days, {hours} hours, {minutes} minutes, {seconds} seconds")