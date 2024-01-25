#CeNTI Library I2C master & Slave

zephyr_include_directories(Master)
zephyr_include_directories(Slave)

target_sources(app PRIVATE Master/CeNTI_I2C_0_Master.c)
target_sources(app PRIVATE Master/CeNTI_I2C_1_Master.c)
target_sources(app PRIVATE Master/CeNTI_I2C_2_Master.c)
target_sources(app PRIVATE Master/CeNTI_I2C_3_Master.c)
target_sources(app PRIVATE Master/CeNTI_I2C_4_Master.c)
target_sources(app PRIVATE Master/CeNTI_I2C_5_Master.c)
target_sources(app PRIVATE Master/CeNTI_I2C_6_Master.c)
target_sources(app PRIVATE Master/CeNTI_I2C_7_Master.c)

target_sources(app PRIVATE Slave/CeNTI_I2C_0_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_I2C_1_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_I2C_2_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_I2C_3_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_I2C_4_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_I2C_5_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_I2C_6_Slave.c)
target_sources(app PRIVATE Slave/CeNTI_I2C_7_Slave.c)