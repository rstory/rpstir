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
package crlv2;
import Algorithms.*;
import extensions.*;
// import serial_number.*;
import name.*;
import asn.*;
public class CrlVersion extends AsnNumericArray
    {
    public AsnObj v1 = new AsnObj();
    public AsnObj v2 = new AsnObj();
    public int constraint()
        {
        AsnIntRef ref = new AsnIntRef(0);
	read(ref);
        if (ref.val == v1._get_sub_tag() || ref.val == v2._get_sub_tag())
            return 1;
        return 0;
        }

    public CrlVersion()
        {
        _tag = AsnStatic.ASN_INTEGER;
        _type = (short)AsnStatic.ASN_INTEGER;
        _set_tag(v1, (int)0);
        _setup((AsnObj)null, v1, (short)(AsnStatic.ASN_ENUM_FLAG), (int)0x0);
        _set_tag(v2, (int)1);
        _setup(v1, v2, (short)(AsnStatic.ASN_ENUM_FLAG), (int)0x0);
        }
    public AsnObj _dup()
        {
        CrlVersion objp = new CrlVersion();
        _set_pointers(objp);
        return objp;
        }

    public CrlVersion index(int index)
        {
        return (CrlVersion)_index_op(index);
        }

    public CrlVersion set(CrlVersion frobj)
        {
        ((AsnObj)this).set(frobj);
	return this;
	}
    }