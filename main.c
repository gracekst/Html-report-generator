#include <stdio.h>
#include <string.h>

void print_item_and_total(float vat, int item_number, FILE *output);

struct company_info
{
    char name[20];
    char phone_number[15];
    char website[30];
};
struct customer_info
{
    char name_lastname[40];
    char phone_number[15];
    char address[80];
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

    printf("Phone number: ");
    fgets(tmp, 20, stdin);
    strcpy(customer.phone_number, tmp);
    
    printf("Address: ");
    fgets(tmp, 80, stdin);
    strcpy(customer.address, tmp);

    float vat;
    printf("Vat: ");
    scanf("%f", &vat);
    
    //get: number of item customer bought
    int item_number = 0;
    do
    {
        printf("Number of items customer bought: ");
        scanf("%d", &item_number);
    }
    while(item_number < 0);
    
    fprintf(output, "<!DOCTYPE>\n");
    fprintf(output,"<html>\n");
    fprintf(output,"<head>\n");
    fprintf(output,"<title>Html report generator</title>\n");
    fprintf(output,"<style>\n");
    fprintf(output,"table, td, th{border: 1px solid black}\n");
    fprintf(output,"th{font-size: 20px; background-color: #D1D1CB; height 55px;}\n");
    fprintf(output,"td{font-size: 20px; text-align: right; height: 40px;}\n");
    fprintf(output,"table{width: 100%%; border-collapse: collapse;}\n");
    fprintf(output,"h1{text-align: center; font-size: 35px;}\n");
    fprintf(output,".input[font-size: 20px; text-align: left; width: 50px;}\n");
    fprintf(output,"</style>\n");
    fprintf(output,"</head>\n");
    fprintf(output,"<body>\n");
    fprintf(output,"<h1>Invoice</h1>\n");
    fprintf(output,"<div class=\"input\">\n");
    fprintf(output,"<b>[%s]</b>", company.name);
    fprintf(output,"<p>Phone number: %s", company.phone_number);
    fprintf(output,"<p>Website: %s", company.website);
    fprintf(output,"<p><br><b>Bill To:</b></p>\n");
    fprintf(output,"<p>%s</p>\n", customer.name_lastname);
    fprintf(output,"<p>%s</p>\n", customer.phone_number);
    fprintf(output,"<p>%s</p>\n", customer.address);
    fprintf(output,"</div>\n");
    fprintf(output,"<table>\n");
    fprintf(output,"<tr>\n");
    fprintf(output,"<th>Item name</th>\n");
    fprintf(output,"<th>Quantity</th>\n");
    fprintf(output,"<th>Price</th>\n");
    print_item_and_total(vat, item_number, output);
    fprintf(output,"</tr>\n");
    fprintf(output,"</table>\n");
    fprintf(output,"</body>\n");
    fprintf(output, "</html>\n");

    fclose(output);

}

void print_item_and_total(float vat, int item_number, FILE *output)
{
    float total = 0;
    for(int i = 0; i < item_number; i++)
    {
        fprintf(output,"<tr>\n");
        char item_name[20];
        printf("Item name(without space): ");
        scanf("%s", item_name);
        fprintf(output,"<td>%s</td>\n", item_name);
        
        int quantity;
        printf("Quatity: ");
        scanf("%d", &quantity);
        fprintf(output,"<td>%d</td>\n", quantity);
        
        float price;
        printf("price: ");
        scanf("%f", &price);
        fprintf(output,"<td>%.2f</td>\n", price*quantity);
        total = total+ (price*quantity);
        fprintf(output,"</tr>\n");
    }
    fprintf(output,"<tr>\n");
    fprintf(output,"<td>Vat %.2f %%</td>\n", vat);
    fprintf(output,"<td colspan=\"2\">%.2f</td>\n", total*(vat/100));
    total = total + total*(vat/100);
    
    fprintf(output,"<tr>\n");
    fprintf(output,"<td>Total</td>\n");
    fprintf(output,"<td colspan=\"2\">%.2f</td>\n", total);
}

