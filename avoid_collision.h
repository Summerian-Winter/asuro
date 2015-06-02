// Code sharing via header file

static void avoid_collision() {
	uint8_t t1, t2;
	t1 = PollSwitch(); Msleep(10); t2 = PollSwitch();
	// Ignore K6 while driving.
	while (t1 && t1 == t2 && t1 & ~K6 && t1 < 64) {
		SerPrint("Collision: "); PrintInt(t1);
		// Stop to get better values.
		SetMotorPower(0, 0);
		Msleep(100);

		t1 = PollSwitch(); Msleep(10); t2 = PollSwitch();
		SerPrint(" "); PrintInt(t1); SerPrint("\n");

		int8_t speedl = 0, speedr = 0;
		if (t1 & (K1 | K2 | K3)) speedl = -70;
		if (t1 & (K4 | K5 | K6)) speedr = -70;
		SetMotorPower(speedl, speedr);

		Msleep(500);
		t1 = PollSwitch(); t2 = PollSwitch();
	}
}

