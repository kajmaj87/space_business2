namespace components {
    struct Position {
        double x, y;
    };

    struct Time {
        int ticks;
        int year;
        int month;
        int day;
        int hour;

        void nextTick(){
            ticks++;
            addHour();
        }

        constexpr auto secondsLastTick(){
            return 3600;
        }

        void addHour(){
            if(hour < 23){
                hour++;
            } else {
                hour = 0;
                addDay();
            }
        }
        void addDay(){
            if(day<30){
                day++;
            } else {
                day = 1;
                addMonth();
            }
        }
        void addMonth(){
            if(month<12){
                month++;
            } else {
                month = 1;
                year++;
            }
        }
    };
}