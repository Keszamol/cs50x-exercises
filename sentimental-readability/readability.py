# ask for userinput
def userinput():
    text = input("Text: ")
    return text


text = userinput()


# average number of letters per 100 words
def average_letters(text):
    letters = []
    words = []
    text_length = len(text)

    for i in range(text_length):  # save only letters
        if text[i].isalpha():
            letters.append(text[i])

    letters_count = len(letters)  # count the letters

    for i in range(text_length):  # count the spaces to get the words
        if text[i].isspace():
            words.append(text[i])

    words_count = len(words) + 1  # +1 for the first word which has no space
    average_letters = (letters_count / words_count) * 100

    return text, text_length, words_count, average_letters


text, text_length, words_count, average_letters = average_letters(text)


# average number of sentences per 100 words
def average_sentences(text, text_length, words_count, average_letters):
    sentences = []

    for i in range(text_length):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':  # count the sentences by counting the symbols
            sentences.append(text[i])

    sentences_count = len(sentences)  # count the sentences

    average_sentences = (sentences_count / words_count) * 100

    return average_sentences


average_sentences = average_sentences(text, text_length, words_count, average_letters)


# implement the coleman-liau index
def coleman_liau(average_letters, average_sentences):
    coleman = (0.0588 * average_letters) - (0.296 * average_sentences) - 15.8
    coleman = round(coleman, 0)
    coleman = int(coleman)

    return coleman


coleman = coleman_liau(average_letters, average_sentences)


# print grade with conditions
def print_conditions(coleman):
    if coleman < 1:
        print("Before Grade 1")
    elif coleman > 16:
        print("Grade 16+")
    else:
        print(f"Grade: {coleman}")


print_conditions(coleman)
