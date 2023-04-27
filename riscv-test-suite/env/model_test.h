// Note: this model uses the nemu_trap to exit the simulation.
// It does not adopt any self-checking mechanism provided by arch-test.
// DiffTest should be used for co-simulation.

#define XLEN 64
#define FLEN 64

#define RVMODEL_HALT \
    mv a0, x0;       \
    .word 0x0005006b

#define RVMODEL_BOOT
#define RVMODEL_DATA_BEGIN
#define RVMODEL_DATA_END
#define RVMODEL_SET_MSW_INT
#define RVMODEL_CLR_MSW_INT
#define RVMODEL_CLR_MTIMER_INT
#define RVMODEL_CLR_MEXT_INT
#define RVMODEL_SET_SSW_INT
#define RVMODEL_CLR_SSW_INT
#define RVMODEL_CLR_STIMER_INT
#define RVMODEL_CLR_SEXT_INT
#define RVMODEL_SET_VSW_INT
#define RVMODEL_CLR_VSW_INT
#define RVMODEL_CLR_VTIMER_INT
#define RVMODEL_CLR_VEXT_INT
#define RVMODEL_IO_WRITE_STR(a, b)
#define RVMODEL_IO_ASSERT_GPR_EQ(a, b, c)
