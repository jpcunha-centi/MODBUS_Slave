#CeNTI Library SPI master & slave

zephyr_include_directories(Master)
zephyr_include_directories(Slave)

target_sources(app PRIVATE Master/CeNTI_SPI_0_Master.c)
target_sources(app PRIVATE Master/CeNTI_SPI_1_Master.c)
target_sources(app PRIVATE Master/CeNTI_SPI_2_Master.c)
target_sources(app PRIVATE Master/CeNTI_SPI_3_Master.c)
target_sources(app PRIVATE Master/CeNTI_SPI_4_Master.c)
target_sources(app PRIVATE Master/CeNTI_SPI_5_Master.c)
target_sources(app PRIVATE Master/CeNTI_SPI_6_Master.c)
target_sources(app PRIVATE Master/CeNTI_SPI_7_Master.c)

target_sources(app PRIVATE Slave/CeNTI_SPI_0_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_SPI_1_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_SPI_2_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_SPI_3_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_SPI_4_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_SPI_5_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_SPI_6_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_SPI_7_Slave.c)