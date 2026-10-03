import requests

if __name__ == "__main__":
    grit_page = requests.get("http://www.umbc.edu").text
    print(grit_page)

    grit_page_list = grit_page.split("</a>")
    print(len(grit_page_list))
