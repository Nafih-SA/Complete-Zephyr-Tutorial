# Zephyr BLE Peripheral
Application demonstrating the BLE Peripheral role.
This sample can be found under :zephyr_file:`samples/bluetooth/peripheral` in the Zephyr tree.

### 1. Macro for declaring 128 bit UUID
**BT_UUID_INIT_128()**

e.g:- static struct bt_uuid_128 vnd_uuid = BT_UUID_INIT_128(\
	0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,\
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

### 2. Service Table creation
```
BT_GATT_SERVICE_DEFINE(vnd_svc,							//Macro that define and register a service
	BT_GATT_PRIMARY_SERVICE(&vnd_uuid),					//Primary Service Declaration Macro
	BT_GATT_CHARACTERISTIC(&vnd_enc_uuid.uuid,			//Characteristic and Value Declaration Macro (Chara uuid,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE |	//Characteristic Attribute properties,
			       BT_GATT_CHRC_INDICATE /*| BT_GATT_CHRC_NOTIFY*/,
			       BT_GATT_PERM_READ_ENCRYPT |			//Characteristic Attribute access permissions,
			       BT_GATT_PERM_WRITE_ENCRYPT,
			       read_vnd, write_vnd, vnd_value),		//read,write Callbacks, Attribute value)
	BT_GATT_CCC(vnd_ccc_cfg_changed,					//Client Characteristic Configuration Declaration Macro
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE_ENCRYPT), //CCC Access permissons
	BT_GATT_CHARACTERISTIC(&vnd_auth_uuid.uuid,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
			       BT_GATT_PERM_READ_AUTHEN |
			       BT_GATT_PERM_WRITE_AUTHEN,
			       read_vnd, write_vnd, vnd_value),
	BT_GATT_CHARACTERISTIC(&vnd_long_uuid.uuid, BT_GATT_CHRC_READ |
			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_EXT_PROP,
			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE |
			       BT_GATT_PERM_PREPARE_WRITE,
			       read_long_vnd, write_long_vnd, &vnd_long_value),
	BT_GATT_CEP(&vnd_long_cep),							//Characteristic Extended Properties Declaration Macro
	BT_GATT_CHARACTERISTIC(&vnd_signed_uuid.uuid, BT_GATT_CHRC_READ |
			       BT_GATT_CHRC_WRITE | BT_GATT_CHRC_AUTH,
			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
			       read_signed, write_signed, &signed_value),
	BT_GATT_CHARACTERISTIC(&vnd_write_cmd_uuid.uuid,
			       BT_GATT_CHRC_WRITE_WITHOUT_RESP,
			       BT_GATT_PERM_WRITE, NULL,
			       write_without_rsp_vnd, &vnd_value),
);
```

### 3. Advertisement Data
```
static volatile uint8_t mfg_data[] = { 0x4c, 0x00, 0x00, 0x00}; // Apple inc
static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
			// BT_UUID_16_ENCODE(BT_UUID_CTS_VAL),
			// BT_UUID_16_ENCODE(BT_UUID_BAS_VAL),
			BT_UUID_16_ENCODE(BT_UUID_HRS_VAL)),
	BT_DATA(BT_DATA_MANUFACTURER_DATA, mfg_data, 4),
	BT_DATA_BYTES(BT_DATA_UUID128_ALL,
		      0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
		      0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12),
};
```