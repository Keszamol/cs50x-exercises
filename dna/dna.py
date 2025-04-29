import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    database = []
    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        dna_sequence = file.read()

    # Get STR sequences from CSV header (skip the first column, which is the name)
    str_sequences = list(database[0].keys())[1:]

    # Find longest match of each STR in the DNA sequence
    computed_str_counts = {}
    for str_seq in str_sequences:
        computed_str_counts[str_seq] = longest_match(dna_sequence, str_seq)

    # Check database for matching profiles
    for person in database:
        match = True
        # Check each STR count against the corresponding database entry
        for str_seq in str_sequences:
            if int(person[str_seq]) != computed_str_counts[str_seq]:
                match = False
                break
        if match:
            print(person["name"])
            return

    # If no match is found, print "No match"
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        count = 0

        # Check for a subsequence match in a "substring" starting at i
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)
    return longest_run


if __name__ == "__main__":
    main()
