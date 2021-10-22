#include <stdio.h>
#include <string.h>
#include <time.h>

struct company_info
{
    char name[20];
    char phone_number[15];
    char website[30];
};
struct customer_info
{
    char name_lastname[40];
    char address[80];
    char phone_number[10];
};

int main(void)
{
    //open a file
    FILE *output;
    output = fopen("Invoice.html", "w");
    //get: company info and assign to struct
    printf("Company information\n");
    struct company_info company;
    char tmp[80];
    printf("Company name: ");
    fgets(tmp, 20, stdin);
    strcpy(company.name, tmp);

    printf("Company phone number: ");
    fgets(tmp, 15, stdin);
    strcpy(company.phone_number, tmp);

    printf("Company website: ");
    fgets(tmp, 30, stdin);
    strcpy(company.website, tmp);

    //get: customer info and assign to struct
    printf("Customer information\n");
    struct customer_info customer;
    printf("Customer name: ");
    fgets(tmp, 40, stdin);
    strcpy(customer.name_lastname, tmp);

    printf("Address: ");
    fgets(tmp, 80, stdin);
    strcpy(customer.address, tmp);

    printf("Phone number: ");
    fgets(tmp, 10, stdin);
    strcpy(customer.phone_number, tmp);
    printf("\n");

    //get: number of item customer bought
    printf("Item information\n");
    int item_number = 0;
    do
    {
        printf("Number of items customer bought: ");
        scanf("%d", &item_number);
    }
    while(item_number < 0);
    //get: item info and assign to struct
    char item_name[item_number][20];
    float price[item_number];
    for(int i = 0; i < item_number; i++)
    {
        printf("Item name: ");
        scanf("%s", item_name[i]);

        printf("price: ");
        scanf("%f", &price[i]);
    }

    //time and date
    time_t t;
    time(&t);
    
    fprintf(output, "<!DOCTYPE html>\n");
    fprintf(output, "<html>");
    //header
    fprintf(output, "<head><title>Invoice</title></head>\n");
    //body
    fprintf(output, "<body>\n");
    //company info
    fprintf(output, "<h1 style=\"letter-spacing: 5px; text-align: center; font-size: 35px; gap: 50px\">INVOICE</h1>\n");
    fprintf(output, "<h2>Company name: %s</h2>\n", company.name);
    fprintf(output, "<p>Date/Time: %s</p>\n",ctime(&t));
    fprintf(output, "<p>Phone number: %s</p>\n", company.phone_number);
    fprintf(output, "<p>Website: %s</p>\n", company.website);
    //customer info
    fprintf(output, "<h2>Bill to:</h2>\n");
    fprintf(output, "<p>Name: %s</p>\n", customer.name_lastname);
    fprintf(output, "<p>Phone number: %s</p>\n", customer.phone_number);
    fprintf(output, "<p>Address: %s</p>\n", customer.address);
    fprintf(output, "<br></br>\n");
    //item_info
    for(int i = 0; i < item_number; i++)
    {
        fprintf(output,"<p style=\"text-align:right;>%s\t\t\t\t\t\t\t%f</p>\n", item_name[i], item_price[i]);
    }
    fprintf(output, "<p style=\"text-align:right;>%f</p>\n", total_price);
    fprintf(output, "</body>\n");
    fprintf(output, "</html>\n");

    fclose(output);


}


