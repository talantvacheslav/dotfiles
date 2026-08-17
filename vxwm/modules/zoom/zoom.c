static float zoom_value(void)
	{
	    const char *display = getenv("DISPLAY");
	    if (!display) return 1.0f;
	
	    char path[64];
	    snprintf(path, sizeof(path), "/tmp/vcompmgr_%s.sock.zoom", display);
	
	    float val = 1.0f;
	    FILE *fp = fopen(path, "r");
	    if (!fp) return 1.0f;
	    if (fscanf(fp, "%f", &val) != 1)
	        val = 1.0f;
	    fclose(fp);
	    return val;
	}
