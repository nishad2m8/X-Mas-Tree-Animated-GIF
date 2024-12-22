#include <M5Cardputer.h>  // Include M5Cardputer library for M5Stack-specific functionality
#include <lvgl.h>
#include <ui.h>
#include "Audio.h"

// https://www.youtube.com/nishad2m8
// https://buymeacoffee.com/nishad2m8

// Create buffers for LVGL display
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[240 * 10];  // Buffer size for 1/10th of screen (240 width)
static lv_color_t buf2[240 * 10];  // Second buffer for double buffering

// microSD card
#define SD_SCK 40
#define SD_MISO 39
#define SD_MOSI 14
#define SD_CS 12

// I2S pins for audio
#define I2S_DOUT 42
#define I2S_BCLK 41
#define I2S_LRCK 43

// MP3 file path
#define AUDIO_FILENAME "/xmas.mp3"

// Audio instance
Audio audio;

// Function to set up the LVGL environment
void lvgl_setup() {
    // Initialize the LVGL library
    lv_init();

    // Initialize the display buffer with two buffers for smoother rendering
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, 240 * 10);

    // Set up the display driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    // Flush callback to send rendered buffer to the M5Cardputer display
    disp_drv.flush_cb = [](lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
        uint32_t w = area->x2 - area->x1 + 1;
        uint32_t h = area->y2 - area->y1 + 1;

        M5.Display.startWrite();
        M5.Display.setAddrWindow(area->x1, area->y1, w, h);
        M5.Display.pushPixels((uint16_t *)&color_p->full, w * h, true);
        M5.Display.endWrite();

        lv_disp_flush_ready(disp_drv);  // Inform LVGL that flushing is done
    };

    // Set the screen resolution
    disp_drv.hor_res = 240;  // Horizontal resolution
    disp_drv.ver_res = 135;  // Vertical resolution
    disp_drv.draw_buf = &draw_buf;

    // Register the display driver
    lv_disp_drv_register(&disp_drv);
}

// Tick handler function for LVGL (called every 10ms)
void lv_tick_task(void *arg) {
    while (1) {
        lv_tick_inc(10);  // Increment LVGL tick by 10ms
        vTaskDelay(pdMS_TO_TICKS(10));  // Delay 10ms
    }
}

// MP3 playback task for smooth audio
void audio_task(void *param) {
    while (1) {
        audio.loop();  // Ensure audio playback continues
        vTaskDelay(1); // Small delay to prevent task starvation
    }
}

// MP3 playback initialization
void start_mp3() {
    audio.stopSong();                      // Stop any current playback
    audio.connecttoFS(SD, AUDIO_FILENAME); // Start playing the MP3
}

void setup() {
    // Initialize M5Cardputer hardware
    Serial.begin(115200);
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Keyboard.begin();
    cfg.serial_baudrate = 115200;
    M5.begin(cfg);

    M5.Display.setRotation(1);  // Rotate the screen
    M5.Lcd.setBrightness(128);  // Set initial brightness to half (128)

    lvgl_setup();   // Initialize LVGL and the display setup

    ui_init();      // Initialize UI from LVGL helper

    // Initialize audio output
    audio.setPinout(I2S_BCLK, I2S_LRCK, I2S_DOUT);
    audio.setVolume(20);

    SPI.begin(SD_SCK, SD_MISO, SD_MOSI);
    if (!SD.begin(SD_CS)) {
        Serial.println(F("ERROR: SD Mount Failed!"));
    }

    // Create a FreeRTOS task for handling LVGL ticks
    xTaskCreatePinnedToCore(lv_tick_task, "lv_tick_task", 4096, NULL, 5, NULL, 1);

    // Start MP3 playback
    start_mp3();

    // Create a FreeRTOS task for audio playback on Core 0
    xTaskCreatePinnedToCore(audio_task, "audio_task", 4096, NULL, 5, NULL, 0);

    // Start animation
    Tree_Animation(ui_Image_Tree, 0);
}

void loop() {
    M5Cardputer.update();
    lv_timer_handler();
    delay(5); // Reduce CPU usage for the main loop
}
