BEGIN {
    state = 2
}
{
    if ($1 == "ping") {
        if (state == 0)
            printf("Two pings!\n");
        state = 0;
    } else if ($1 == "pong") {
        if (state == 1)
            printf("Two pongs!\n");
        state = 1;
    }

}
