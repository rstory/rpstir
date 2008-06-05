/* ***** BEGIN LICENSE BLOCK *****
 * 
 * BBN Rule Editor/Engine for Address and AS Number PKI
 * Verison 1.0
 * 
 * COMMERCIAL COMPUTER SOFTWARE�RESTRICTED RIGHTS (JUNE 1987)
 * US government users are permitted restricted rights as
 * defined in the FAR.  
 *
 * This software is distributed on an "AS IS" basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 * Copyright (C) BBN Technologies 2007.  All Rights Reserved.
 *
 * Contributor(s):  Charlie Gardiner
 *
 * ***** END LICENSE BLOCK ***** */
package extensions;
import orname.*;
import name.*;
import Algorithms.*;
// import serial_number.*;
import asn.*;
public class IPAddressOrRange extends AsnArray
    {
    public AsnBitString addressPrefix = new AsnBitString();
    public IPAddressRange addressRange = new IPAddressRange();
    public IPAddressOrRange()
        {
        _tag = AsnStatic.ASN_CHOICE;
        _type = (short)AsnStatic.ASN_CHOICE;
        _setup((AsnObj)null, addressPrefix, (short)0, (int)0x0);
        _setup(addressPrefix, addressRange, (short)0, (int)0x0);
        }
    public AsnObj _dup()
        {
        IPAddressOrRange objp = new IPAddressOrRange();
        _set_pointers(objp);
        return objp;
        }

    public IPAddressOrRange index(int index)
        {
        return (IPAddressOrRange)_index_op(index);
        }

    public IPAddressOrRange set(IPAddressOrRange frobj)
        {
        ((AsnObj)this).set(frobj);
	return this;
	}
    }