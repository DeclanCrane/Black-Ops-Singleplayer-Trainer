#include "Viewmodel.h"

void SmoothViewmodel()
{
    if (*bAiming > 0.f)
    {
        // Set variables of old viewmodel values
        if (!bADS)
        {
            bADS = true;

            viewmodelX = *(float*)(*cg_gun_x + 0x18);
            viewmodelY = *(float*)(*cg_gun_y + 0x18);
            viewmodelZ = *(float*)(*cg_gun_z + 0x18);
        }

        if (*bAiming < 1.f)
        {
            *(float*)(*cg_gun_x + 0x18) = *(float*)(*cg_gun_x + 0x18) * (*bAiming * -1.f);
            *(float*)(*cg_gun_y + 0x18) = *(float*)(*cg_gun_y + 0x18) * (*bAiming * -1.f);
            *(float*)(*cg_gun_z + 0x18) = *(float*)(*cg_gun_z + 0x18) * (*bAiming * -1.f);
        }
    }

    if (*bAiming == 0.f && bADS)
    {
        *(float*)(*cg_gun_x + 0x18) = viewmodelX;
        *(float*)(*cg_gun_y + 0x18) = viewmodelY;
        *(float*)(*cg_gun_z + 0x18) = viewmodelZ;

        bADS = false;
    }
}
