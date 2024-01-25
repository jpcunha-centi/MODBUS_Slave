#CeNTI Library UART Asynchronous & Ring buffer

zephyr_include_directories(ASync)
zephyr_include_directories(RingBuffer)

target_sources(app PRIVATE ASync/CeNTI_UART_0_ASync.c)
target_sources(app PRIVATE ASync/CeNTI_UART_1_ASync.c)
target_sources(app PRIVATE ASync/CeNTI_UART_2_ASync.c)
target_sources(app PRIVATE ASync/CeNTI_UART_3_ASync.c)
target_sources(app PRIVATE ASync/CeNTI_UART_4_ASync.c)
target_sources(app PRIVATE ASync/CeNTI_UART_5_ASync.c)
target_sources(app PRIVATE ASync/CeNTI_UART_6_ASync.c)
target_sources(app PRIVATE ASync/CeNTI_UART_7_ASync.c)

target_sources(app PRIVATE RingBuffer/CeNTI_UART_0_RingBuffer.c)
target_sources(app PRIVATE RingBuffer/CeNTI_UART_1_RingBuffer.c)
target_sources(app PRIVATE RingBuffer/CeNTI_UART_2_RingBuffer.c)
target_sources(app PRIVATE RingBuffer/CeNTI_UART_3_RingBuffer.c)
target_sources(app PRIVATE RingBuffer/CeNTI_UART_4_RingBuffer.c)
target_sources(app PRIVATE RingBuffer/CeNTI_UART_5_RingBuffer.c)
target_sources(app PRIVATE RingBuffer/CeNTI_UART_6_RingBuffer.c)
target_sources(app PRIVATE RingBuffer/CeNTI_UART_7_RingBuffer.c)