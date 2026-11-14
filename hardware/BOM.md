# E2G Bill of Materials / 物料清单

This is the major-component BOM reconstructed from the original build records. Passive components that are not listed here should be confirmed against the PCB files and assembled board before ordering.

本清单根据原始装配记录整理，列出主要机械、气动和电子元件。未列出的阻容等无源器件，应在采购前根据 PCB 文件和实物板再次确认。

## Mechanical and pneumatic parts / 机械与气动件

| Ref. | Qty. | Component | Specification | Installation notes |
|---|---:|---|---|---|
| M1 | As required | Countersunk screw / 沉头螺丝 | M2 × 8 mm | Quantity depends on the enclosure and printed-part revision / 数量按外壳和打印件版本确定 |
| P1 | 1 | Male-to-male brass fitting / 铜对丝 | G1/8 (1 分), 18.5 mm long, 7.7 mm bore, 10 mm across flats | Inspect thread sealing before pressure testing / 加压前检查螺纹密封 |
| P2 | 1 | Cylinder / 气缸 | 75% cylinder / 75% 气缸 | Install with the opening advanced forward / 开口超前安装 |
| P3 | 3 | O-ring / O 形圈 | 24 × 2.4 mm | Lubricate with a material-compatible grease / 使用与密封材料兼容的润滑脂 |
| P4 | 1 | Solenoid valve / 电磁阀 | MAC 35A-ACA-DDA-1BA, 12 V, 5.4 W | Confirm the coil marking before wiring / 接线前核对线圈铭牌 |
| P5 | 1 | Pusher-nozzle rubber tip / 推嘴胶头 | Standard configuration shown in the original build / 原装配记录中的标准配置 | Check fit and sealing surface / 检查配合及密封面 |

## Controller modules and connectors / 控制模块与连接器

| Ref. | Qty. | Component | Specification | Notes |
|---|---:|---|---|---|
| U1 | 1 | Arduino Pro Mini | ATmega328P, 5 V, 16 MHz | Main controller / 主控制器 |
| U2 | 1 | Bluetooth serial module / 蓝牙透传模块 | BT04-E | UART transparent transmission / UART 串口透传 |
| J1 | 1 | Straight pin header / 直针座 | PH2.0, 7P | Match PCB footprint and polarity / 核对 PCB 封装和方向 |
| J2 | 1 | Right-angle pin header / 弯针座 | PH2.0, 7P | Match PCB footprint and polarity / 核对 PCB 封装和方向 |
| J3 | 1 | Straight pin header / 直针座 | XH2.54, 4P | Match PCB footprint and polarity / 核对 PCB 封装和方向 |

## Semiconductors / 半导体器件

| Ref. | Qty. | Component | Model | Package | Function |
|---|---:|---|---|---|---|
| Q1 | 1 | N-channel MOSFET | SI2302, marking A2sHB | SOT-23 | Low-side switching / 低边开关 |
| U3 | 1 | 5 V linear regulator | L78M05CDT / 78M05 | TO-252 / DPAK | 5 V rail / 5 V 电源 |
| U4 | 1 | 3.3 V LDO regulator | LN1154B332MR-G | SOT-23-5 | 3.3 V rail / 3.3 V 电源 |

## Switches / 开关

| Ref. | Qty. | Component | Model or size | Mounting |
|---|---:|---|---|---|
| SW1 | 1 | Self-locking push-button / 自锁按键 | 5.8 × 5.8 mm, six-pin | Horizontal side-actuated through-hole / 卧式六脚侧按插板 |
| SW2 | 1 | Tactile switch / 轻触开关 | Rjsvm 3 × 6 × 2.5 mm | SMD side-actuated / 贴片侧按 |
| SW3 | 1 | Travel-detection switch / 行程检测开关 | Shinmei SW1AB-264-1T25 | Miniature SMD / 小型贴片 |

## Procurement checks / 采购检查

- Confirm whether the assembled controller uses the 12 V / 5.4 W MAC coil shown in the original order record. Do not substitute a 24 V coil without checking the driver and supply.
- Confirm the orientation of all PH and XH connectors against the PCB silkscreen before soldering.
- Check the MOSFET pinout and top marking because SI2302-compatible parts from different suppliers may use different markings.
- Verify regulator pinout, thermal pad, and package dimensions against the Gerber footprint.
- The screw quantity and unlisted passive components remain revision-dependent.

- 根据原始采购记录，MAC 阀采用 12 V / 5.4 W 线圈。替换成 24 V 型号前必须核对驱动电路和供电。
- 焊接前根据 PCB 丝印确认 PH、XH 插座方向。
- 不同供应商的 SI2302 顶部丝印可能不同，采购时需要核对引脚定义。
- 根据 Gerber 焊盘确认稳压器的引脚、散热焊盘和封装尺寸。
- 螺丝数量及未列出的无源器件随硬件版本而变化。

