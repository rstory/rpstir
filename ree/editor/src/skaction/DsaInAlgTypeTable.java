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
package skaction;
import name.*;
import Algorithms.*;
import certificate.*;
import crlv2.*;
import asn.*;
public class DsaInAlgTypeTable extends AsnChoice
    {
    public AsnInteger bits = new AsnInteger();
    public DSS_Parms parms = new DSS_Parms();
    public DsaInAlgTypeTable()
        {
        _tag = AsnStatic.ASN_CHOICE;
        _type = (short)AsnStatic.ASN_CHOICE;
        _setup((AsnObj)null, bits, (short)0, (int)0x0);
        _setup(bits, parms, (short)0, (int)0x0);
        }
    public DsaInAlgTypeTable set(DsaInAlgTypeTable frobj)
        {
        ((AsnObj)this).set(frobj);
	return this;
	}
    }