import data_download


def is_user_sure():
    print("Do you really want to start the download? it may take long time")
    answer = input(" [Y/n]: ")
    if answer == "Y":
        return True
    return False


def main():
    print("What do you want to do?")

    print("dl to download list of books")
    print("db to download books info")
    print("dt to download books texts")
    choice = input("Your choice: ").strip()

    # download
    if choice == "dl":
        if is_user_sure():
            data_download.save_book_list()
    elif choice == "db":
        how_many_books = int(input("How many books do you want to download? (type -1 for all): "))
        if is_user_sure():
            data_download.save_data_for_books(how_many_books)
    elif choice == "dt":
        if is_user_sure():
            data_download.save_texts()
    else:
        print("incorrect choice")


if __name__ == '__main__':
    main()
