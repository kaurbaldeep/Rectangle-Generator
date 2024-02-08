# Import necessary libraries for plotting and handling CSV files.
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import csv

# Initialize lists to store rectangle information
x_coords = [] # List to store X coordinates of rectangles.
y_coords = [] # List to store Y coordinates of rectangles.
span_values = [] # List to store widths (spans) of rectangles.
elevation_values = [] # List to store heights (elevations) of rectangles.

# Read rectangle data from the CSV file
with open('anglesForRectangle.csv', 'r') as csvfile:
    csvreader = csv.reader(csvfile)

    # Iterate through each row in the CSV file.
    for row in csvreader:
        # Extract data from the row and convert them to float.
        x = float(row[0]) # X coordinate of the rectangle.
        y = float(row[1]) # Y coordinate of the rectangle.
        span_val = float(row[2])  # Width (span) of the rectangle.
        elevation_val = float(row[3]) # Height (elevation) of the rectangle.
        # Append the extracted data to respective lists.
        x_coords.append(x) 
        y_coords.append(y)
        span_values.append(span_val)
        elevation_values.append(elevation_val)

# Create a figure and axis
fig, ax = plt.subplots()

# Add rectangles to the plot
for x, y, span, elevation in zip(x_coords, y_coords, span_values, elevation_values):
    # Iterate through the lists of X coordinates (x_coords), Y coordinates (y_coords),
    # widths (span_values), and heights (elevation_values) simultaneously using the zip function.
    # For each set of coordinates and dimensions, create a Rectangle patch object and add it to the plot.
    rect = patches.Rectangle((x - span / 2, y - elevation / 2), span, elevation, linewidth=1, edgecolor='blue', facecolor='none')
    ax.add_patch(rect)

# Set axis labels and title
plt.xlabel('X Coordinate')
plt.ylabel('Y Coordinate')
plt.title('Rectangles on the Graph')

# Set axis limits based on the data
plt.xlim(min(x_coords) - max(span_values), max(x_coords) + max(span_values))
plt.ylim(min(y_coords) - max(elevation_values), max(y_coords) + max(elevation_values))

# Show the plot
plt.grid(True)
plt.show()