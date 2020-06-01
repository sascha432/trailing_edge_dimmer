# Print Settings

***NOTE*** **WORK IN PROGRESS, STL FILES MIGHT CHANGE AND FILES ARE MISSING**

Print settings are for CURA 4.x and tested with a CR10S PRO

Temperature settings depend on your PLA/ABS/PETG and build surface.

## Safety and fire hazards

***If mains voltage or high currents are involved, make sure everything is adequately protected.***

**It is highly recommended to use Flame Retardant ABS or Polycarbonate Filament for any parts that involve electricity.**

ABS that is exposed to high temperatures (>60°C) has the tendency to become very brittle over time. Keep that in mind for areas important for structural integrity. Adding slots for inserting pieces of aluminium is a good option.

### Further protection of plastic against heat

A layer of aluminium tape and Kapton on top protects plastic pretty well for a short period of time, even if a gas torch is used trying to light it up. Areas around fuses that are prone to high heat and burning plasma when they blow, can be protected this way. Do not use glas fuses, but sand filled/ceramic ones that do not explode and proper ceramic fuse holders. Areas where cables are connected (screw/crimp terminals etc...) should be protected this way too.

### Parts

### Housing

- Use flame retardant ABS or polycarbonate
- Custom support required
- The screw holes for the plate are 5mm/0.8mm, then 5mm/2.6mm. Use a drill (max. 10mm depth) to adjust it and use a thread cutter if desired.

## Plate

- Use flame retardant ABS/PC with high infill
- No support required

## Rocker switch

- Can be PLA or PETG, my favorite is PETG
- No support required
- The angled switch consists of two parts that need to be glued together (cyanoacrylate) to get a perfect smooth surface
- The clip that holds the switch in the plate should be printed with PETG or ABS

## Warping

Warping is usually the result of an incorrect z-height, dirty surface, flow rate, wrong temperature (bed, nozzle, environment), fan speed/fan duct or draft.

- Wash your PEI sheet with dishwashing detergent, rinse with plenty of hot water and use gloves. Repeat the process a couple times. Isopropyl alcohol can be used to remove minor dirt, but grease/dust is usually spread around if not rinsed well
- Clean glas or Kapton with acetone
- Adjust your z-height while printing by adding a couple more lines of skirt/brim
- For ABS: Increasing or decreasing the amount of infill can prevent warping. If your slicer supports different infill, use 65-80% infill for the first 10mm height to prevent uneven expansion during cooling
- If warping occurs on one side, the direction of the fan duct might be the reason
- Make it stick with ABS juice (works for ABS and PLA), glue stick, hair spray or if nothing helps, use a raft

## Support

- Support density 15-20%
- Support floor/roof interface 0.64mm (4 layers), density 20-35%
- Placement everywhere
- Z-distance 0.16mm
- If the support cannot be removed, use fan override, increase Z-distance and check if the flow rate is too high
- **For ABS**: Fan override off, if it causes warping
- Make sure to disable "Generate Support" after changing settings

## Using custom support

- Load both files into CURA
- Select the support and change per model settings to "print as support"
- Select both models (Ctrl+A = select all) and right click, merge models (or Ctrl+Alt+G)
- Verify that the support and model position match and z-height is 0mm
- Disable "Generate Support"

## Shell/Infill

- Layer height 0.16mm
- Wall 1.2mm
- Top/Bottom 1.2mm
- Horizontal expansion **-0.16mm**. Make sure to run a test print if holes and dimensions are correct. If not use scaling (100.25% for example) and adjust horizontal expansion
- Housing (ABS): 20-30% infill, cubic or gyroid
- Plate and rocker switch: 75-85% infill, lines
- Speed 50mm, 15mm for intial layer

## PLA

Settings for a PEI flex sheet.

- Skirt 2-3 lines to clean the nozzle
- Nozzle 195-200°C
- Bed temperature intial layers (2-3) 75°C, then 60°C
- Retraction 5mm, speed 45mm
- Fan speed 100%
- Bridge settings can be enabled

Some PLA does not stick well and tends to warp. I am using a raft with 10mm margin for those cases or print on glas/Kapton with ABS juice.

## ABS

Settings for a flex steel sheet with Kapton tape. Glas works very well too, but it is hard to remove the bigger the surface. Aluminium works to a certain degree if the surface is rough enough (wet sanding paper, grit ~400).

If the Kapton tape does not stick, make sure to wash your plate with dishwashing detergent, rinse with plenty of hot water and clean it with acetone before applying the tape. Heat it up to 120°C and use a lot pressure to make it stick very well. If air bubbles cannot the removed, use a needle to pinch tiny holes into the tape. **Repeat the process** of heating it up and appling pressure to the area where the model has been removed.

- Use ABS juice to make it stick. It can be highly diluted with acetone
- Make sure the fan is off at all times, no bridge settings
- Brim 10mm or 10 lines of skirt, distance 1mm, draft shield 1mm, height 5mm. That prevents warping very well
- Nozzle 220-235°C
- Bed temperature 85-90°C
- Retraction 5mm, speed 50mm
- Heated chamber 40°C

## PETG

Settings for a PEI flex sheet.

- Nozzle 220°C
- Bed temperature 75°C
- Retraction 6.8mm, speed 80mm
- Brim 10mm or a raft with 10mm, if warping occurs
- Fan speed 50%
- Bridge settings can be enabled
