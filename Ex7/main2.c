#include <stdio.h>
#include <stdlib.h>

typedef struct Books
{
    int id;
    int price;
    char title[100];
} book_t;

void total_price(void)
{
    FILE *fp;
    book_t book;
    int total = 0;

    fp = fopen("Book.bin", "rb");

    if (fp == NULL)
    {
        printf("Cannot open Book.bin\n");
        return;
    }

    while (fread(&book, sizeof(book_t), 1, fp) == 1)
    {
        total += book.price;
    }

    fclose(fp);

    printf("\nTotal Price = %d\n", total);
}

void list_books(void)
{
    FILE *fp;
    book_t book;

    fp = fopen("Book.bin", "rb");

    if (fp == NULL)
    {
        printf("Cannot open Book.bin\n");
        return;
    }

    printf("\n========== Book List ==========\n");
    printf("%-5s %-8s %s\n", "ID", "Price", "Title");
    printf("---------------------------------------------\n");

    while (fread(&book, sizeof(book_t), 1, fp) == 1)
    {
        printf("%-5d %-8d %s\n",
               book.id, book.price, book.title);
    }

    fclose(fp);
}

int main()
{
    book_t books[6] =
    {
        {1, 1000, "All the Light We Cannot See"},
        {2, 300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4, 550, "Killers of the Flower Moon"},
        {5, 870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    FILE *fp;

    fp = fopen("Book.bin", "wb");

    if (fp == NULL)
    {
        printf("File open error!\n");
        return 0;
    }

    fwrite(books, sizeof(book_t), 6, fp);

    fclose(fp);

    printf("Book data saved successfully!\n");

    total_price();

    list_books();

    return 0;
}
