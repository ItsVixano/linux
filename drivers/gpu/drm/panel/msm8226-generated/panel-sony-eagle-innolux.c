// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2025 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct innolux {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline struct innolux *to_innolux(struct drm_panel *panel)
{
	return container_of(panel, struct innolux, panel);
}

static void innolux_reset(struct innolux *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
}

static int innolux_on(struct innolux *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf0,
					 0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb6, 0x05);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb7, 0x70, 0x70);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb8,
					 0x01, 0x04, 0x04, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xbc, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc7,
					 0x00, 0xff, 0xff, 0x10, 0x10, 0x0a,
					 0x0b, 0xff, 0xff, 0x93, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf0,
					 0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb0, 0x0a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb1, 0x0a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb2, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb3, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb4, 0x06);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb6, 0x44);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb7, 0x34);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb8, 0x14);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb9, 0x35);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xba, 0x14);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc2, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd0,
					 0x0f, 0x0f, 0x10, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd1,
					 0x00, 0x05, 0x00, 0x11, 0x00, 0x23,
					 0x00, 0x38, 0x00, 0x42, 0x00, 0x62,
					 0x00, 0x84, 0x00, 0xb7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd2,
					 0x00, 0xe2, 0x01, 0x21, 0x01, 0x5e,
					 0x01, 0xb1, 0x01, 0xfb, 0x01, 0xfc,
					 0x02, 0x4a, 0x02, 0xa5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd3,
					 0x03, 0x11, 0x03, 0x53, 0x03, 0x81,
					 0x03, 0xa7, 0x03, 0xb7, 0x03, 0xc5,
					 0x03, 0xcc, 0x03, 0xd8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd4,
					 0x03, 0xf6, 0x03, 0xff);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd5,
					 0x00, 0x05, 0x00, 0x0f, 0x00, 0x22,
					 0x00, 0x33, 0x00, 0x43, 0x00, 0x60,
					 0x00, 0x7b, 0x00, 0xb2);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd6,
					 0x00, 0xe1, 0x01, 0x29, 0x01, 0x68,
					 0x01, 0xbf, 0x02, 0x06, 0x02, 0x0a,
					 0x02, 0x55, 0x02, 0xb5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd7,
					 0x03, 0x15, 0x03, 0x4d, 0x03, 0x79,
					 0x03, 0xa3, 0x03, 0xb1, 0x03, 0xc3,
					 0x03, 0xcc, 0x03, 0xdc);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd8,
					 0x03, 0xf1, 0x03, 0xff);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd9,
					 0x00, 0x05, 0x00, 0x0e, 0x00, 0x20,
					 0x00, 0x32, 0x00, 0x43, 0x00, 0x5f,
					 0x00, 0x79, 0x00, 0xaa);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xdd,
					 0x00, 0xd4, 0x01, 0x1d, 0x01, 0x59,
					 0x01, 0xb4, 0x01, 0xec, 0x01, 0xed,
					 0x02, 0x35, 0x02, 0x97);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xde,
					 0x02, 0xd5, 0x03, 0x2d, 0x03, 0x61,
					 0x03, 0x9a, 0x03, 0xab, 0x03, 0xbe,
					 0x03, 0xc8, 0x03, 0xd5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xdf,
					 0x03, 0xfb, 0x03, 0xff);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe0,
					 0x00, 0x01, 0x00, 0x0c, 0x00, 0x1f,
					 0x00, 0x32, 0x00, 0x41, 0x00, 0x61,
					 0x00, 0x80, 0x00, 0xb3);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe1,
					 0x00, 0xdf, 0x01, 0x21, 0x01, 0x5b,
					 0x01, 0xaf, 0x01, 0xfb, 0x01, 0xfc,
					 0x02, 0x4a, 0x02, 0xa8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe2,
					 0x02, 0xef, 0x03, 0x52, 0x03, 0x81,
					 0x03, 0xa6, 0x03, 0xb7, 0x03, 0xc4,
					 0x03, 0xcb, 0x03, 0xd8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe3,
					 0x03, 0xf6, 0x03, 0xff);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe4,
					 0x00, 0x01, 0x00, 0x0a, 0x00, 0x1d,
					 0x00, 0x2e, 0x00, 0x3f, 0x00, 0x5c,
					 0x00, 0x77, 0x00, 0xae);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe5,
					 0x00, 0xdf, 0x01, 0x28, 0x01, 0x69,
					 0x01, 0xbf, 0x02, 0x04, 0x02, 0x07,
					 0x02, 0x53, 0x02, 0xb3);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe6,
					 0x03, 0x13, 0x03, 0x4c, 0x03, 0x79,
					 0x03, 0xa3, 0x03, 0xb0, 0x03, 0xc3,
					 0x03, 0xcc, 0x03, 0xdc);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe7,
					 0x03, 0xf1, 0x03, 0xfe);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe8,
					 0x00, 0x01, 0x00, 0x0a, 0x00, 0x1b,
					 0x00, 0x2d, 0x00, 0x3e, 0x00, 0x5b,
					 0x00, 0x75, 0x00, 0xa6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe9,
					 0x00, 0xd1, 0x01, 0x1a, 0x01, 0x57,
					 0x01, 0xb2, 0x01, 0xe9, 0x01, 0xeb,
					 0x02, 0x35, 0x02, 0x95);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xea,
					 0x02, 0xd3, 0x03, 0x2b, 0x03, 0x61,
					 0x03, 0x9a, 0x03, 0xab, 0x03, 0xbe,
					 0x03, 0xc8, 0x03, 0xd5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xeb,
					 0x03, 0xfb, 0x03, 0xff);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf0,
					 0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb3, 0x00);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 125);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 100);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x2c);
	mipi_dsi_usleep_range(&dsi_ctx, 1000, 2000);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0050);
	mipi_dsi_usleep_range(&dsi_ctx, 1000, 2000);

	return dsi_ctx.accum_err;
}

static int innolux_off(struct innolux *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 150);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 150);

	return dsi_ctx.accum_err;
}

static int innolux_prepare(struct drm_panel *panel)
{
	struct innolux *ctx = to_innolux(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	innolux_reset(ctx);

	ret = innolux_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int innolux_unprepare(struct drm_panel *panel)
{
	struct innolux *ctx = to_innolux(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = innolux_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode innolux_mode = {
	.clock = (540 + 130 + 2 + 30) * (960 + 56 + 2 + 16) * 60 / 1000,
	.hdisplay = 540,
	.hsync_start = 540 + 130,
	.hsync_end = 540 + 130 + 2,
	.htotal = 540 + 130 + 2 + 30,
	.vdisplay = 960,
	.vsync_start = 960 + 56,
	.vsync_end = 960 + 56 + 2,
	.vtotal = 960 + 56 + 2 + 16,
	.width_mm = 59,
	.height_mm = 104,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int innolux_get_modes(struct drm_panel *panel,
			     struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &innolux_mode);
}

static const struct drm_panel_funcs innolux_panel_funcs = {
	.prepare = innolux_prepare,
	.unprepare = innolux_unprepare,
	.get_modes = innolux_get_modes,
};

static int innolux_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness = backlight_get_brightness(bl);
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness(dsi, brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return 0;
}

// TODO: Check if /sys/class/backlight/.../actual_brightness actually returns
// correct values. If not, remove this function.
static int innolux_bl_get_brightness(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness(dsi, &brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return brightness & 0xff;
}

static const struct backlight_ops innolux_bl_ops = {
	.update_status = innolux_bl_update_status,
	.get_brightness = innolux_bl_get_brightness,
};

static struct backlight_device *
innolux_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 255,
		.max_brightness = 255,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &innolux_bl_ops, &props);
}

static int innolux_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct innolux *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 2;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS |
			  MIPI_DSI_MODE_VIDEO_NO_HFP;

	drm_panel_init(&ctx->panel, dev, &innolux_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = innolux_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void innolux_remove(struct mipi_dsi_device *dsi)
{
	struct innolux *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id innolux_of_match[] = {
	{ .compatible = "innolux" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, innolux_of_match);

static struct mipi_dsi_driver innolux_driver = {
	.probe = innolux_probe,
	.remove = innolux_remove,
	.driver = {
		.name = "panel-innolux",
		.of_match_table = innolux_of_match,
	},
};
module_mipi_dsi_driver(innolux_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for innolux QHD video mode dsi panel for speed up");
MODULE_LICENSE("GPL");
