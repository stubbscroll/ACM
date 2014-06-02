for %%s in (*.png) do convert %%s -compress None -depth 24 %%~ns.bmp
