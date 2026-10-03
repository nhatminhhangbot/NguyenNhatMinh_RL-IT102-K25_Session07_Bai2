#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;          
    float ratedPowerKW; 
};

struct EnergySensor {
    float voltageVolts;      
    float currentAmperes;     
    int unoccupancyMinutes;   
};

int main() {
    struct SmartDevice dev;
    struct EnergySensor sen;
    float operatingHours = 0.0f;

    printf("====================================================\n");
    printf("   HE THONG QUAN LY NANG LUONG - RIKKEI SMARTHOME   \n");
    printf("====================================================\n");
    
    printf("Nhap ma dinh danh thiet bi (deviceID): ");
    if (scanf("%d", &dev.deviceID) != 1) {
    	return 0;
	}

    printf("Nhap ten thiet bi (deviceName): ");
    scanf("%49s", dev.deviceName);

    printf("Nhap trang thai ban dau (status - 1: Bat, 0: Tat): ");
    if (scanf("%d", &dev.status) != 1) {
    	return 0;
	}

    printf("Nhap cong suat dinh muc (ratedPowerKW - kW): ");
    if (scanf("%f", &dev.ratedPowerKW) != 1) {
    	return 0;
	}

    printf("Nhap dien ap do duoc tu cam bien (voltageVolts - V): ");
    if (scanf("%f", &sen.voltageVolts) != 1) {
    	return 0;
	}

    printf("Nhap dong dien do duoc tu cam bien (currentAmperes - A): ");
    if (scanf("%f", &sen.currentAmperes) != 1) {
    	return 0;
	}

    printf("Nhap thoi gian vang nguoi lien tuc (unoccupancyMinutes - phut): ");
    if (scanf("%d", &sen.unoccupancyMinutes) != 1) {
    	return 0;
	}

    printf("Nhap so gio van hanh trong thang (operatingHours): ");
    if (scanf("%f", &operatingHours) != 1) {
    	return 0;
	}

    if (sen.voltageVolts < 0 || sen.currentAmperes < 0 || sen.unoccupancyMinutes < 0 || dev.ratedPowerKW < 0) {
        printf("\n[LOI HE THONG] Phat hien thong so cam bien hoac cong suat bi am (< 0)!\n");
        printf("Day la dau hieu loi phan cung. He thong da huy thao tac xu ly.\n");
        return 0;
    }

    if (operatingHours <= 0 || operatingHours > 744.0f) {
        printf("\n[LOI HE THONG] So gio van hanh trong thang khong hop le (%.2f gio)!\n", operatingHours);
        printf("Yeu cau phai tu > 0 va khong vuot qua 744 gio (31 ngay). Tu choi tinh toan.\n");
        return 0;
    }

    if (sen.currentAmperes > 30.0f) {
        dev.status = 0;
        printf("\n================ [CANH BAO NGUY HIEM] ================\n");
        printf("Phat hien dong dien vuot nguong an toan: %.2f A (> 30.0 A)!\n", sen.currentAmperes);
        printf("Kich hoat CHE ÐO NGAT KHAN CAP phong chong chay no.\n");
        printf("Trang thai thiet bi da duoc chuyen ve: 0 (Da tat).\n");
        printf("=======================================================\n");
    }
    else if (dev.status == 1 && sen.unoccupancyMinutes >= 15) {
        dev.status = 0;
        printf("\n================ [THONG BAO TIET KIEM] ===============\n");
        printf("Thiet bi dang bat nhung phong vang nguoi lien tuc %d phut (>= 15 phut).\n", sen.unoccupancyMinutes);
        printf("He thong tu dong TAT thiet bi de tiet kiem nang luong.\n");
        printf("Trang thai thiet bi da duoc chuyen ve: 0 (Da tat).\n");
        printf("=======================================================\n");
    } else {
        printf("\n[TRANG THAI] He thong van hanh an toan. Trang thai thiet bi duy tri: %s\n", 
               (dev.status == 1) ? "Dang bat (1)" : "Da tat (0)");
    }

    float totalKWh = dev.ratedPowerKW * operatingHours;
    float remainingKWh = totalKWh;
    
    float cost1 = 0.0f, cost2 = 0.0f, cost3 = 0.0f, cost4 = 0.0f;

    if (remainingKWh > 0) {
        float kwh1 = (remainingKWh > 50.0f) ? 50.0f : remainingKWh;
        cost1 = kwh1 * 1806.0f;
        remainingKWh -= kwh1;
    }

    if (remainingKWh > 0) {
        float kwh2 = (remainingKWh > 50.0f) ? 50.0f : remainingKWh;
        cost2 = kwh2 * 1866.0f;
        remainingKWh -= kwh2;
    }

    if (remainingKWh > 0) {
        float kwh3 = (remainingKWh > 100.0f) ? 100.0f : remainingKWh;
        cost3 = kwh3 * 2167.0f;
        remainingKWh -= kwh3;
    }
    
    if (remainingKWh > 0) {
        float kwh4 = remainingKWh;
        cost4 = kwh4 * 2729.0f;
    }

    float totalCostVND = cost1 + cost2 + cost3 + cost4;

    printf("\n============= BAO CAO HE THONG SMARTHOME =============\n");
    printf("- Ma thiet bi (deviceID)     : %d\n", dev.deviceID);
    printf("- Ten thiet bi (deviceName)  : %s\n", dev.deviceName);
    printf("- Trang thai sau xu ly       : %s\n", (dev.status == 1) ? "Dang bat (1)" : "Da tat (0)");
    printf("- Cong suat dinh muc         : %.2f kW\n", dev.ratedPowerKW);
    printf("- Dien ap do duoc            : %.2f V\n", sen.voltageVolts);
    printf("- Dong dien do duoc          : %.2f A\n", sen.currentAmperes);
    printf("- Thoi gian vang nguoi       : %d phut\n", sen.unoccupancyMinutes);
    printf("- Thoi gian van hanh trong   : %.2f gio\n", operatingHours);
    printf("------------------------------------------------------\n");
    printf("- Tong dien nang tieu thu    : %.2f kWh\n", totalKWh);
    printf("- Tong tien dien (chua VAT)  : %.2f VND\n", totalCostVND);
    printf("======================================================\n");

    return 0;
}
