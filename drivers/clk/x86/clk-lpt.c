/*
 * Intel Lynxpoint LPSS clocks.
 *
 * Copyright (C) 2013, Intel Corporation
 * Authors: Mika Westerberg <mika.westerberg@linux.intel.com>
 *	    Heikki Krogerus <heikki.krogerus@linux.intel.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#define PRV_CLOCK_PARAMS 0x800

static int lpt_clk_probe(struct platform_device *pdev)
{
	struct clk *clk;

	/* LPSS free running clock */
	clk = clk_register_fixed_rate(&pdev->dev, "lpss_clk", NULL, CLK_IS_ROOT,
				      100000000);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	/* Shared DMA clock */
	clk_register_clkdev(clk, "hclk", "INTL9C60.0.auto");
	return 0;
}

static struct platform_driver lpt_clk_driver = {
	.driver = {
		.name = "clk-lpt",
		.owner = THIS_MODULE,
	},
	.probe = lpt_clk_probe,
};

int __init lpt_clk_init(void)
{
	return platform_driver_register(&lpt_clk_driver);
}
