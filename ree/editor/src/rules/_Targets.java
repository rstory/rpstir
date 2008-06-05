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
package rules;
import name.*;
import asn.*;
public class _Targets extends AsnRef
    {
    public Targets ref;
    public _Targets()
        {
        _tag = AsnStatic.ASN_SEQUENCE;
        _type = (short)AsnStatic.ASN_SEQUENCE;
        _flags |= AsnStatic.ASN_POINTER_FLAG;
        }
    public void add()
	{
	ref = new Targets();
	add((AsnObj)ref);
	}
    }