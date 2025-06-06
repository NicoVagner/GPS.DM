import csv

# Open the input and output files
with open('templates_273.txt', 'r') as infile, open('output.csv', 'w', newline='') as outfile:
    # Create a CSV writer object
    writer = csv.writer(outfile)

    # Write the header
    writer.writerow(['x', 'y', 'Value'])

    # Read each line of the input file
    for line in infile:
        # Split the line by whitespace
        parts = line.split()

        # Extract Clock Number and Window values
        clock_number = parts[2]
        window = parts[4]
        value = parts[6]

        # Write to the CSV file
        writer.writerow([clock_number, window, value])

print("CSV file generated successfully!")