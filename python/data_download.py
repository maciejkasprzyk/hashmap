import json
import requests
import os
import pathlib


python_path = os.path.dirname(os.path.abspath(__file__))
data_path = pathlib.Path(python_path).parent / 'data'


books_urls_list_path = data_path / 'url_list.txt'
books_info_path = data_path / 'books_info.json'
authors_info_ready_path = data_path / 'authors_info_ready.json'
authors_info_raw_path = data_path / 'authors_info_raw.json'
books_texts_path = data_path / 'books_text.json'


def save_book_list():
    """
    Gets full list of books stored on wolnelektury.pl and saves into txt file
    :return: -
    """
    book_list = "https://wolnelektury.pl/api/books/"

    response_book_list = requests.get(book_list)

    data_book_list = response_book_list.text
    parsed_book_list = json.loads(data_book_list)
    url_list = [book["href"] for book in parsed_book_list]

    with open(books_urls_list_path, 'w') as file:
        for url in url_list:
            file.write("%s\n" % url)


def get_info_for_book(book_url):
    """
    Function get data for given book from wolnelektury.pl
    :param book_url: Link to certain book via API on website: wolnelektury.pl
    :return: data in dictionary structure
    """

    response_book_info = requests.get(book_url)
    data_book_info = response_book_info.text
    parsed_book_info = json.loads(data_book_info)

    return parsed_book_info


def save_data_for_books(book_count=-1):
    """
    Gets data for given number of books listed in file: url_list.txt and saves it in a file.
    When given count < 0 then function loads all books available
    :return: -
    """
    with open(books_urls_list_path, 'r') as file:
        book_list = file.readlines()

    books_data = []

    if book_count == 0:
        return
    elif book_count < 0:
        book_count = len(book_list)

    for i, url in enumerate(book_list):

        if not i < book_count:
            break
        book_data = get_info_for_book(url)
        books_data.append(book_data)
        print(f'{book_data["title"]}')
        print(f"downloaded {i + 1} of {book_count} books")

    with open(books_info_path, 'w') as file:
        json.dump(books_data, file)


def save_texts():
    """Iterate over json books info file and download all texts"""
    with open(books_info_path, 'r') as file:
        books_data = json.load(file)

    books_texts = {}

    for i, book in enumerate(books_data):
        title = book["title"]
        txt_url = book["txt"]

        book_pure_txt = None
        if txt_url is not None and txt_url != '':
            response_txt = requests.get(txt_url)
            data_txt = response_txt.text
            footer_sign = "-----"
            footer_position = data_txt.find(footer_sign)

            if footer_position != -1:
                book_without_footer = data_txt[:footer_position]
            else:
                book_without_footer = data_txt
            header_sign = "ISBN"
            header_last_position = book_without_footer.find(header_sign)
            isbn_length = 4 + 1 + 13 + 4 + 1

            if header_last_position != -1:
                book_pure_txt = book_without_footer[header_last_position + isbn_length:].strip()
            else:
                book_pure_txt = book_without_footer.strip()

        print(title)
        print(f"downloaded {i + 1} of {len(books_data)} books")
        books_texts[title] = book_pure_txt

    with open(books_texts_path, 'w') as file:
        json.dump(books_texts, file)
