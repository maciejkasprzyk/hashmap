import json
import sys
import re


def get_raw_text():
    """

    :return: one long string containing all the texts
    """
    with open('books_text.json') as file:
        texts = json.load(file)

    result = ''
    for book_text in texts.values():
        if book_text:
            result += book_text
    return result


def get_words(text, n=None):
    """Takes a string containing raw text and return list of parsed unique words."""
    words = set()
    # print(len(text.split()))
    for word in text.split():
        if n and len(words) > n:
            break
        # dont add words containing digits or capital letters
        digits = '[0-9ĄBCĆDEĘFGHIJKLŁMNŃOÓPRSŚTUWYZŹŻ]'
        if re.search(digits, word):
            continue

        # remove unwanted leading and trailing characters
        letters = 'aąbcćdeęfghijklłmnńoóprsśtuwyzźż'
        non_letters = '^[^' + letters + ']*|[^' + letters + ']*$'
        word = re.sub(non_letters, "", word)

        # skip words containing non-letters characters
        if re.search('[^' + letters + ']', word):
            continue
        # dont add short words
        if len(word) < 3:
            continue
        words.add(word)
        print("Parsed", len(words), "words.")
    return words


def print_usage_then_exit():
    print("Error parsing arguments. The syntax is:\ngenerator.py [-n NUMBER] FILE")
    exit(-1)


def main():
    argc = len(sys.argv)
    path = None
    n = None
    # noinspection PyBroadException
    try:
        i = 1
        while i < argc:
            x = sys.argv[i]
            if x.startswith('-'):
                if x != '-n':
                    raise SyntaxError()
                else:
                    i += 1
                    n = int(sys.argv[i])
            else:
                path = x
            i += 1
    except Exception:
        print_usage_then_exit()

    if path is None or n is None:
        print_usage_then_exit()

    print(f'Saving {n} words to file {path}.')
    raw = get_raw_text()
    words = get_words(raw, n=n)
    with open(path, "w+") as file:
        for word in words:
            file.write(f"{word}\n")


if __name__ == '__main__':
    main()
