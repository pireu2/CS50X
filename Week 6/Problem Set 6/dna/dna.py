import csv
import sys


def main():
    # TODO: Check for command-line usage
    check_input()
    # TODO: Read database file into a variable
    db = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            db.append(row)
    # TODO: Read DNA sequence file into a variable
    input = ""
    with open(sys.argv[2], "r") as file:
        for line in file:
            input = line
    # TODO: Find longest match of each STR in DNA sequence
    current = {}
    for seq in db[0]:
        if seq != "name":
            current[seq] = str(longest_match(input, seq))

    # TODO: Check database for matching profiles
    name = "No match"
    for person in db:
        copy = person.copy()
        copy.pop("name")
        if copy == current:
            name = person["name"]
    print(name)

    return


def check_input():
    if len(sys.argv) < 3:
        sys.exit("Too few command-line arguments")
    elif len(sys.argv) > 3:
        sys.exit("Too many command-line arguments")

    _, extension1 = sys.argv[1].split(".")
    _, extension2 = sys.argv[2].split(".")
    if extension1 != "csv":
        sys.exit("Not a CSV file")
    try:
        open(f"{sys.argv[1]}", "r")
    except FileNotFoundError:
        sys.exit("File does not exist")
    if extension2 != "txt":
        sys.exit("Not a TXT file")
    try:
        open(f"{sys.argv[2]}", "r")
    except FileNotFoundError:
        sys.exit("File does not exist")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
