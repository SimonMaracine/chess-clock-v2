#pragma once

namespace chess_clock
{
    unsigned long get_current_time();

    template<unsigned long TickTime>
    class Timer
    {
    public:
        void reset()
        {
            m_last_time = get_current_time();
        }

        bool tick()
        {
            const unsigned long current_time {get_current_time()};

            if (current_time - m_last_time > TickTime)
            {
                m_last_time = current_time;

                return true;
            }

            return false;
        }
    private:
        unsigned long m_last_time {0};  // Milliseconds
    };
}
