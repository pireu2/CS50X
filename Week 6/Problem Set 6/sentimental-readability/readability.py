def main():
    str = input("Text: ")
    L = (count_letters(str) / count_words(str)) * 100
    S = (count_sentences(str) / count_words(str)) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


def count_letters(str):
    num = 0
    for letter in str:
        if letter.isalpha():
            num += 1
    return num


def count_words(str):
    return str.count(" ") + 1


def count_sentences(str):
    num = 0
    for letter in str:
        if letter in [".", "!", "?"]:
            num += 1
    return num


if __name__ == "__main__":
    main()
