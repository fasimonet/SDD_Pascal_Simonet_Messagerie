int main()
{
    time_t t = time(NULL);
    struct tm temps;
    printf("La date actuelle est : %d/%d/%d \n", temps.tm_day, temps.tm_mon, temps.tm_year);
    return 0;
}