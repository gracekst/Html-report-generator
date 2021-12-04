
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_SIZE 50

struct company_info
{
    char name[VAR_SIZE];
    char phone_number[VAR_SIZE];
    char website[VAR_SIZE];
};
struct customer_info
{
    char name_lastname[VAR_SIZE];
    char phone_number[VAR_SIZE];
    char address[VAR_SIZE];
};
struct item_info
{
    char name[VAR_SIZE];
    char quantity[VAR_SIZE];
    char price[VAR_SIZE];
};


int main(void)
{
    //input: vat
    float vat = 0;
    do
    {
        printf("Vat: ");
        scanf("%f", &vat);
    }
    while(vat < 0);

    //company, customer info part
    char info_filename[VAR_SIZE] = {0};
    printf("Input company and customer info filename: ");
    scanf("%s", info_filename);

    //declare struct
    struct company_info company;
    struct customer_info customer;
    char *assign_struct[6] = {company.name, company.phone_number, company.website, customer.name_lastname, customer.phone_number, customer.address};

    //open a file in read mode
    FILE *info_file = fopen(info_filename, "r");
    if(info_file == NULL)
    {
        printf("Can't open a file");
        exit(1);
    }

    char line[VAR_SIZE];
    int i = 0;
    while(fgets(line, VAR_SIZE, info_file))
    {
        strcpy(assign_struct[i], line);
        i++;
    }
    fclose(info_file);

    //item info part
    char item_filename[VAR_SIZE] = {0};
    printf("Input item info filename: ");
    scanf("%s", item_filename);

    //open a file in read mode
    int item_amount;
    char tmp[VAR_SIZE] = {0};
    FILE *read_file = fopen(item_filename, "r");
    //get item amount from a first line of item info file
    fgets(tmp, VAR_SIZE, read_file);
    item_amount = atoi(tmp);

    //read from file and assign to a array of struct
    struct item_info item[item_amount];
    char tmp2[100] = {0};
    fread(&tmp2, sizeof(char), 100, read_file);

    char *item_tmp = strtok(tmp2, "\n");
    int count = 1;
    int struct_count = 0;
    while(item_tmp != NULL)
    {
        if(count % 3 == 1)
        {
            strcpy(item[struct_count].name, item_tmp);
        }
        else if(count % 3 == 2)
        {
            strcpy(item[struct_count].quantity, item_tmp);
        }
        else if(count % 3 == 0)
        {
            strcpy(item[struct_count].price, item_tmp);
            struct_count++;
        }
        count++;
        item_tmp = strtok(NULL,"\n");
    }
    fclose(read_file);

    //writing an output file with html code
    FILE *output = fopen("output.html", "w");
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
    float total = 0;
    for(int i = 0; i < item_amount; i++)
    {
        fprintf(output,"<tr>\n");
        fprintf(output,"<td>%s</td>\n", item[i].name);

        fprintf(output,"<td>%s</td>\n", item[i].quantity);

        fprintf(output,"<td>%s</td>\n", item[i].price);
        int quantity = atoi(item[i].quantity);
        float price = atof(item[i].price);
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
    fprintf(output,"</tr>\n");
    fprintf(output,"</table>\n");
    fprintf(output,"</body>\n");
    fprintf(output, "</html>\n");

    fclose(output);

}
